include_directories(${PROJECT_SOURCE_DIR}/src
	${Boost_INCLUDE_DIR})
					
add_executable(remote_logger
	remote_logger.cpp)

target_link_libraries(remote_logger
	websocketpp)