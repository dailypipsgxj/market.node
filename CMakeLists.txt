cmake_minimum_required(VERSION 2.8)

project(MARKETBOOST)

ADD_SUBDIRECTORY(lib)

add_definitions(-std=c++11 -stdlib=libc++ -g -O0 -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64)

set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -stdlib=libc++")

include_directories(
    ${MARKETBOOST_SOURCE_DIR}/include
    ${uv_SOURCE_DIR}/include
    ${http_parser_SOURCE_DIR}
)

add_executable(
    http_gateway
    ${MARKETBOOST_SOURCE_DIR}/src/http/gateway.cpp
)

target_link_libraries(
    http_gateway
    uv
    http_parser
)

