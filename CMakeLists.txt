cmake_minimum_required(VERSION 2.8)

project(MARKETNODE)

ADD_SUBDIRECTORY(lib)

if (CMAKE_COMPILER_IS_CLANG) 
    add_definitions(
        -std=c++11
        -stdlib=libc++
        -g
        -O0
        -D_LARGEFILE_SOURCE
        -D_FILE_OFFSET_BITS=64
    )

    set(
        CMAKE_CXX_LINK_FLAGS 
        "${CMAKE_CXX_LINK_FLAGS} -stdlib=libc++"
    )
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(
        -std=c++11
        -g
        -O0
        -D_LARGEFILE_SOURCE
        -D_FILE_OFFSET_BITS=64
    )
endif()

include_directories(
    ${MARKETNODE_SOURCE_DIR}/include
    ${uv_SOURCE_DIR}/include
    ${http_parser_SOURCE_DIR}
)

add_executable(
    http_gateway
    ${MARKETNODE_SOURCE_DIR}/src/http/gateway.cpp
)

add_executable(
    design
    ${MARKETNODE_SOURCE_DIR}/src/model/order.cpp
    ${MARKETNODE_SOURCE_DIR}/test/design.cpp
)

if (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")  
    target_link_libraries( 
        design
        cxxrt
        c++
    )

    target_link_libraries(
        http_gateway
        uv
        http_parser
        cxxrt
        c++
    )
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin") 
    target_link_libraries(
        http_gateway
        uv
        http_parser
    )
endif()
