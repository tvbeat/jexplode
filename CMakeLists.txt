
cmake_minimum_required(VERSION 3.0)
project(jexplode)
set(PACKAGE_VERSION "0.01")

set(CMAKE_CXX_COMPILER      "g++")
set(CMAKE_CXX_FLAGS         "-W -Wall --std=gnu++14")
set(CMAKE_CXX_FLAGS_DEBUG   "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)

