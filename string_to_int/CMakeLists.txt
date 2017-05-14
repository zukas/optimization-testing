cmake_minimum_required(VERSION 2.8)

project(string_to_int)
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} benchmark)

