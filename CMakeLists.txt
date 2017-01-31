cmake_minimum_required(VERSION 3.6)
project(GraphIsomorphism)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(SOURCE_FILES main.cpp Graph.h Graph.cpp GraphTest.h)
add_executable(GraphIsomorphism ${SOURCE_FILES})