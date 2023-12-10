cmake_minimum_required(VERSION 3.26)
project(tool)

set(CMAKE_CXX_STANDARD 23)

set(YAML_CPP_DIR "./libs/yaml-cpp-0.8.0/")

add_subdirectory(${YAML_CPP_DIR})

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

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

target_link_libraries(tool PRIVATE yaml-cpp)
