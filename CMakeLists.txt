cmake_minimum_required(VERSION 2.8)
project(websocketpp CXX)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

option(WEBSOCKETPP_BUILD_EXAMPLES "Build the websocketpp example programs" OFF)

if (WIN32)
	set(BOOST_ROOT "C:\\Boost")
endif()
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.50.0 REQUIRED COMPONENTS System Date_Time Regex Thread)


add_subdirectory(src)

if (WEBSOCKETPP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
