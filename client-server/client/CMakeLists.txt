cmake_minimum_required(VERSION 3.5)
project(client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        ../common
)


set(SOURCE_FILES
        client.cpp
        ../common/common.cpp)

add_executable(client ${SOURCE_FILES})