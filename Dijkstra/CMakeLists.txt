cmake_minimum_required(VERSION 3.29)
project(Dijkstra)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS_DISTRIBUTION"-03")

add_executable(Dijkstra
        DK.cpp)
