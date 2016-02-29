cmake_minimum_required(VERSION 3.3)
project(tbb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ltbb")

set(SOURCE_FILES main.cpp)
add_executable(tbb ${SOURCE_FILES})