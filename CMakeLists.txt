cmake_minimum_required(VERSION 3.2)

project(ORCA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w")

add_subdirectory(src)
add_subdirectory(experiments)
add_subdirectory(visualization)