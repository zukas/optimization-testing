cmake_minimum_required(VERSION 2.8)
project(optimization_testing)

include_directories(benchmark/include)
add_subdirectory(benchmark)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fno-exceptions -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")


add_subdirectory(string_to_int)
add_subdirectory(geometry)
