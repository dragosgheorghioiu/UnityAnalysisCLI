cmake_minimum_required(VERSION 3.26)
project(tool)

set(CMAKE_CXX_STANDARD 23)

add_executable(tool main.cpp
        Args.cpp
        Args.h
        Process.cpp
        Process.h)
