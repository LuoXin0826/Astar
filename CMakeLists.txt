
cmake_minimum_required (VERSION 2.8.11)
project (Astar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(astar astar.cc)

add_executable(main main.cc)
target_link_libraries(main astar)