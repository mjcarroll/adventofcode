cmake_minimum_required(VERSION 3.10)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 17)

set(AOC_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(common/aoc_config.hh.in aoc_config.hh)
include_directories(common ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(2015)
add_subdirectory(2019)

