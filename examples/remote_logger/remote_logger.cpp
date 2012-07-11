/*
 * Copyright (c) 2012, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#include "../../src/websocketpp.hpp"

#include <cstring>
#include <set>

#include <boost/functional.hpp>
#include <boost/bind.hpp>

using websocketpp::server;

// Logger server handler that receives connections and allows broadcasting
// messages to them.
class logger_server_handler : public server::handler {
public:
    
    // register a new client
    void on_open(connection_ptr con) {
        boost::lock_guard<boost::mutex> guard(m_mutex);
        m_connections.insert(con);
    }
    
    // remove an exiting client
    void on_close(connection_ptr con) {
        boost::lock_guard<boost::mutex> guard(m_mutex);
        m_connections.erase(con);
    }

	// broadcast to all clients
	void broadcast(std::string msg) {
		boost::lock_guard<boost::mutex> guard(m_mutex);
		for (connection_set::const_iterator ci = m_connections.begin();
			ci != m_connections.end();
			ci++) {
				(*ci)->send(msg, websocketpp::frame::opcode::TEXT);
		}
	}

private:
	typedef std::set<connection_ptr> connection_set;
	
    connection_set                      m_connections;    
    boost::mutex                        m_mutex;    // guards m_connections
};

// Logger class that allows logging to all connected clients. First construct
// an instance, start the sevice and then log away.
class Logger {
public:
	Logger(unsigned short _port)
		: port(_port)
	{}

	void startService() {
		loggerServerHandler = new logger_server_handler();
		boost::thread serviceThread(&Logger::startupThread, this);
	}
	
	void log(std::string msg) {
		loggerServerHandler->broadcast(msg);
	}
	
private:
	void startupThread() {
		try {       
	        server::handler::ptr handler(loggerServerHandler);
	        server endpoint(handler);

	        endpoint.alog().unset_level(websocketpp::log::alevel::ALL);
	        endpoint.elog().unset_level(websocketpp::log::elevel::ALL);

	        endpoint.alog().set_level(websocketpp::log::alevel::CONNECT);
	        endpoint.alog().set_level(websocketpp::log::alevel::DISCONNECT);

	        endpoint.elog().set_level(websocketpp::log::elevel::RERROR);
	        endpoint.elog().set_level(websocketpp::log::elevel::FATAL);

	        std::cout << "Starting WebSocket telemetry server on port " << port << std::endl;
	        endpoint.listen(port);
	    } catch (std::exception& e) {
	        std::cerr << "Exception: " << e.what() << std::endl;
	    }			
	}
	
	unsigned short port;
	logger_server_handler* loggerServerHandler;
};

int main(int argc, char* argv[]) {
    unsigned short port = 9007;
        
    if (argc == 2) {
        port = atoi(argv[1]);
        
        if (port == 0) {
            std::cout << "Unable to parse port input " << argv[1] << std::endl;
            return 1;
        }
    }
    
	Logger logger(port);
	logger.startService();
	
	while(true) {
		logger.log("hello, world!");
		boost::this_thread::sleep(boost::posix_time::seconds(1));
	}
    
    return 0;
}
