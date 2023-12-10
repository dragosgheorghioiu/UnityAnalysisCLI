cmake_minimum_required(VERSION 3.26)
project(tool)

set(CMAKE_CXX_STANDARD 23)


set(YAML_CPP_DIR "./libs/yaml-cpp-0.8.0/")

add_subdirectory(${YAML_CPP_DIR})

# Add your source files
add_executable(tool
        main.cpp
        Args.cpp
        Args.h
        Process.cpp
        Process.h
        SceneAnalyzer.cpp
        SceneAnalyzer.h
        GameObject.cpp
        GameObject.h
        Scene.cpp
        Scene.h
        Script.cpp
        Script.h
)

target_link_libraries(tool PRIVATE yaml-cpp)
