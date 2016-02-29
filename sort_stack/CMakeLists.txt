cmake_minimum_required(VERSION 3.3)
project(sort_stack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(sort_stack ${SOURCE_FILES})