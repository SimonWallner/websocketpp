include_directories(${PROJECT_SOURCE_DIR}/src
	${Boost_INCLUDE_DIR})
					

add_executable(broadcast_server_tls
	broadcast_server_tls.cpp)

target_link_libraries(broadcast_server_tls
	websocketpp)