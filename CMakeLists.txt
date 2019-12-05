cmake_minimum_required(VERSION 3.10)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 17)

set(extra_cmake_args)
if(DEFINED CMAKE_BUILD_TYPE)
  list(APPEND extra_cmake_args -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
endif()
list(APPEND extra_cmake_args "-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
list(APPEND extra_cmake_args "-DSPDLOG_BUILD_BENCH=OFF")
list(APPEND extra_cmake_args "-DSPDLOG_BUILD_TESTS=OFF")
list(APPEND extra_cmake_args "-DSPDLOG_BUILD_EXAMPLES=OFF")

include(ExternalProject)
# Get spdlog 1.3.1
ExternalProject_Add(spdlog-1.3.1
  URL https://github.com/gabime/spdlog/archive/v1.3.1.tar.gz
  URL_MD5 3c17dd6983de2a66eca8b5a0b213d29f
  TIMEOUT 600
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/spdlog
    ${extra_cmake_args}
    -Wno-dev
)
ExternalProject_Get_Property(spdlog-1.3.1 SOURCE_DIR)
add_library(spdlog::spdlog INTERFACE IMPORTED)
set_target_properties(spdlog::spdlog PROPERTIES
  INTERFACE_INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/spdlog/include")
add_dependencies(spdlog::spdlog DEPENDS spdlog-1.3.1)


set(AOC_PROJECT_DIR ${CMAKE_SOURCE_DIR})
configure_file(${CMAKE_SOURCE_DIR}/common/aoc_config.hh.in
               ${CMAKE_BINARY_DIR}/common/aoc_config.hh)

add_library(aoc_common
  ./common/aoc_common.cc
  ./common/aoc_main.cc
)
target_include_directories(aoc_common
  PUBLIC
  common
  ${CMAKE_BINARY_DIR}/common
  ${CMAKE_CURRENT_BINARY_DIR}/spdlog/include
  )
target_link_libraries(aoc_common PUBLIC spdlog::spdlog)

macro(register_solution YEAR DAY)
  add_executable(${YEAR}_${DAY} day${DAY}.cc)
  target_link_libraries(${YEAR}_${DAY} aoc_common spdlog::spdlog)
endmacro()

add_subdirectory(2015)
add_subdirectory(2019)
