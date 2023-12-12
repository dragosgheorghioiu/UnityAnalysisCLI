cmake_minimum_required(VERSION 3.26)
project(tool)

set(CMAKE_CXX_STANDARD 23)

set(YAML_CPP_DIR "./libs/yaml-cpp-0.8.0/")

add_subdirectory(${YAML_CPP_DIR})

find_package(OpenMP)

# Add your source files
add_executable(tool
        main.cpp
        src/Args.cpp
        src/Args.h
        src/Process.cpp
        src/Process.h
        src/SceneAnalyzer.cpp
        src/SceneAnalyzer.h
        src/GameObject.cpp
        src/GameObject.h
        src/Scene.cpp
        src/Scene.h
        src/Script.cpp
        src/Script.h
)

target_link_libraries(tool PRIVATE yaml-cpp OpenMP::OpenMP_CXX)
