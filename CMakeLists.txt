cmake_minimum_required(VERSION 2.8)
project(websocketpp CXX)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

option(WEBSOCKETPP_BUILD_EXAMPLES "Build the websocketpp example programs" OFF)

find_package(Boost REQUIRED COMPONENTS System Date_Time Regex Thread)
find_package(OpenSSL REQUIRED)


add_subdirectory(src)

if (WEBSOCKETPP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(WEBSOCKETPP_BUILD_EXAMPLES)