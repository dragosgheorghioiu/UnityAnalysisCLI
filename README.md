# Unity Analysis Tool

## Description
The tool is used to analyze Unity projects and it can achieve the following functions:
- `.unity` file parsing
- dumps the scene hierarchy
- dumps unused scripts in a csv file
- paralelized using OpenMP

## Build
```
mkdir build
cd build
cmake ..
```

## Usage
```
tool.exe /path/to/unity/project /path/to/output
```

## Libraries
- [yaml-cpp](https://github.com/jbeder/yaml-cpp/)
- [OpenMP](https://www.openmp.org/)
