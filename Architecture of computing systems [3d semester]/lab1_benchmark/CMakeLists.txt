cmake_minimum_required(VERSION 2.8)

project(benchmarking)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src )
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#message( ${PROJECT_SOURCE_DIR} )

#add_executable(benchmarking main.cpp)
add_executable(benchmarking ${PROJECT_SOURCE_DIR}/main.cpp)