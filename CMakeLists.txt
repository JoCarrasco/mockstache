cmake_minimum_required(VERSION 4.1)
project(mockstache)

set(CMAKE_CXX_STANDARD 17)

add_executable(mockstache src/main.cpp
        src/projects/projects.cpp
        src/projects/projects.h
        src/utils/utils.cpp
        src/utils/utils.h)
