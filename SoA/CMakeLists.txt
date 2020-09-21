cmake_minimum_required(VERSION 2.8)

project(SoA)

add_subdirectory(glm)

include_directories(glm)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
add_definitions(-DGLM_FORCE_AVX)
add_definitions(-DGLM_FORCE_ALIGNED)

add_compile_options(-mavx)
add_compile_options(-msse4.2)



#define GLM_FORCE_SSE2 // or GLM_FORCE_SSE42 if your processor supports it
#define GLM_FORCE_ALIGNED

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} benchmark)

