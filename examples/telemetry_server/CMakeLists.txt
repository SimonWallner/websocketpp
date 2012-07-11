include_directories(${PROJECT_SOURCE_DIR}/src
	${Boost_INCLUDE_DIR})
					
add_executable(telemetry_server
	telemetry_server.cpp)

target_link_libraries(telemetry_server
	websocketpp)