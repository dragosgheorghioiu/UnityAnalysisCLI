#ifndef TOOL_PROCESS_H
#define TOOL_PROCESS_H


#include "Args.h"
#include "SceneAnalyzer.h"
#include "Scene.h"
#include <fstream>
#include <memory>
#include <filesystem>
#include <list>


class Process {
private:
    std::unique_ptr<Args> args;
    std::vector<Scene> scenes;
public:
    Process(int argc, char **argv);
    void populateScenePaths(std::filesystem::path &dirPath);
    void populateSceneChildren();
    void run();
    void createOutputDirectory();
    static void printChild(const std::string &child, const std::map<int, GameObject> &gameObjectMap,
                    const int &depth, std::ofstream &fout);
    void printSceneHierarchy(const Scene &scene, std::ofstream &fout);
};


#endif //TOOL_PROCESS_H
