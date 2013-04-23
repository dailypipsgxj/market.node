cmake_minimum_required(VERSION 2.8)

project(MARKETBOOST)

FIND_PACKAGE( Boost 1.53 COMPONENTS system thread regex program_options REQUIRED )

add_definitions(-g -O0 -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64)

include_directories(
    ${MARKETBOOST_SOURCE_DIR}/include
)

add_executable(
    server
    src/http/connection.cpp
    src/http/io_service_pool.cpp
    src/http/main.cpp
    src/http/mime_types.cpp
    src/http/reply.cpp
    src/http/request_handler.cpp
    src/http/request_parser.cpp
    src/http/server.cpp
)

target_link_libraries(
    server
    ${Boost_LIBRARIES}
)

