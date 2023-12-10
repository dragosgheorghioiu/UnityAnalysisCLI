#ifndef TOOL_PROCESS_H
#define TOOL_PROCESS_H


#include "Args.h"
#include "SceneAnalyzer.h"
#include "Scene.h"
#include "Script.h"
#include <fstream>
#include <memory>
#include <filesystem>
#include <list>


class Process {
private:
    std::unique_ptr<Args> args;
    std::unordered_map<std::string, Script> scripts;
    std::vector<Scene> scenes;
public:
    Process(int argc, char **argv);
    void populateAllScripts(std::filesystem::path dirPath);
    void populateScenePaths(std::filesystem::path dirPath);
    void analyzeProject();
    void run();
    void createOutputDirectory();
    static void printChild(const std::string &child, const std::map<int, GameObject> &gameObjectMap,
                    const int &depth, std::ofstream &fout);
    void printSceneHierarchy(const Scene &scene, std::ofstream &fout);
    void dumpSceneHeirarchy();
    void searchForScriptsInDir(const std::filesystem::path &dirPath);
    void
    createUnusedScriptCSV(const std::unordered_map<std::string, Script> &scripts,
                          const std::filesystem::path &outputPath);
};


#endif //TOOL_PROCESS_H
