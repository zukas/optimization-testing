cmake_minimum_required(VERSION 2.8)

project(code_test_2)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer" )

add_executable(${PROJECT_NAME} "main.cpp" "caseone.cpp" "caseone.h")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
