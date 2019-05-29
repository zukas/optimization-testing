cmake_minimum_required(VERSION 2.8)

project(devirtualize)

file(GLOB SOURCE
    *.cpp
    *.h
    )

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} benchmark)

