cmake_minimum_required(VERSION 2.8)

project(geometry)

add_executable(${PROJECT_NAME}
    "main.cpp" "common.h"
    "node1.cpp" "node1.h"
    "node2.cpp" "node2.h"
    "node3.cpp" "node3.h"
    "node4.cpp" "node4.h"
    "node5.cpp" "node5.h"
    "node6.cpp" "node6.h")

target_link_libraries(${PROJECT_NAME} benchmark)
