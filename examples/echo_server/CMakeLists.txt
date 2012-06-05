include_directories(${PROJECT_SOURCE_DIR}/src
	${Boost_INCLUDE_DIR})
					

add_executable(echo_server
	echo_server.cpp)

target_link_libraries(echo_server
	websocketpp)