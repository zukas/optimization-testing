cmake_minimum_required(VERSION 2.8)

project(sc_test7)

file(GLOB SOURCE_SC
    *.cpp
    *.h
)

add_executable(${PROJECT_NAME} ${SOURCE_SC})
target_link_libraries(${PROJECT_NAME} benchmark)
