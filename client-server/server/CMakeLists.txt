cmake_minimum_required(VERSION 3.5)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        ../common
)


set(SOURCE_FILES
        server.cpp
        ../common/common.cpp)

add_executable(server ${SOURCE_FILES})