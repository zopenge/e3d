# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    e3d
    VERSION 0.1
    DESCRIPTION "e3d CMake projects built with VSCode")

SET(ROOT_DIR ${CMAKE_SOURCE_DIR})

add_subdirectory(src/platform)