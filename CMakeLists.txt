cmake_minimum_required(VERSION 3.27)
project(EngineTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(modules)
add_subdirectory(src)