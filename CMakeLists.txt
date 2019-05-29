cmake_minimum_required(VERSION 2.8)
project(optimization_testing)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE "" INTERNAL FORCE)

include_directories(benchmark/include)
add_subdirectory(benchmark)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fno-exceptions -fno-rtti -std=c++14")

add_subdirectory(concepts)
add_subdirectory(devirtualize)
add_subdirectory(string_to_int)
add_subdirectory(geometry)
add_subdirectory(bitop)
add_subdirectory(standard_containers)
