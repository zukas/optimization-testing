cmake_minimum_required(VERSION 2.8)

project(common_types)

file(GLOB SOURCE_CT
    *.cpp
    *.h
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCE_CT})
