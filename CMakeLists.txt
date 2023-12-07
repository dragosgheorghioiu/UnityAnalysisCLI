cmake_minimum_required(VERSION 3.26)
project(tool)

set(CMAKE_CXX_STANDARD 23)

find_package(yaml-cpp REQUIRED)

add_executable(tool main.cpp
        Args.cpp
        Args.h
        Process.cpp
        Process.h
        SceneAnalyzer.cpp
        SceneAnalyzer.h
        GameObject.cpp
        GameObject.h
        Scene.cpp
        Scene.h)

target_link_libraries(tool yaml-cpp)
