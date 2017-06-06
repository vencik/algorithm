cmake_minimum_required(VERSION 2.8)
project("Various algorithms" CXX)
enable_testing()

# Version
set(ALGORITHM_VERSION_MAJOR 0)
set(ALGORITHM_VERSION_MINOR 1)
set(ALGORITHM_VERSION_PATCH 0)

# Config. header file
configure_file(
    "${PROJECT_SOURCE_DIR}/config.hxx.in"
    "${PROJECT_BINARY_DIR}/config.hxx")

# C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror --std=c++11 -O2")

# Allow inclusion of the config. header file
include_directories("${PROJECT_BINARY_DIR}")

# Subdirectories
add_subdirectory(algorithm)
add_subdirectory(cli)
add_subdirectory(unit_test)
