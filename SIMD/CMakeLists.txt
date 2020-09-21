cmake_minimum_required(VERSION 2.8)

project(SIMD)

add_compile_options(-mavx)
add_compile_options(-msse4.2)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} benchmark)


