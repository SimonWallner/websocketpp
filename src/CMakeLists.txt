include_directories(${PROJECT_SOURCE_DIR}/src
					${Boost_INCLUDE_DIR})
					
link_directories(
	${Boost_LIBRARY_DIRS}
)

# for some reason the compiler skips the file if in c mode...???
set_source_files_properties(md5/md5.c PROPERTIES LANGUAGE CXX )

add_library(websocketpp STATIC
	base64/base64.cpp
	md5/md5.c
	messages/data.cpp
	network_utilities.cpp
	processors/hybi_header.cpp
	processors/hybi_util.cpp
	sha1/sha1.cpp
	uri.cpp)

target_link_libraries(websocketpp
	${Boost_SYSTEM_LIBRARY}
	${Boost_DATE_TIME_LIBRARY}
	${Boost_REGEX_LIBRARY}
	${Boost_THREAD_LIBRARY}
	${OPENSSL_SSL_LIBRARY}
	${OPENSSL_CRYPTO_LIBRARY})