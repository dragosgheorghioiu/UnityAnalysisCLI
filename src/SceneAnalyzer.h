#ifndef TOOL_SCENEANALYZER_H
#define TOOL_SCENEANALYZER_H

#include "GameObject.h"
#include "Script.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "yaml-cpp/yaml.h"
#include <filesystem>

/**
 * Class to analyze a scene file.
 */
class SceneAnalyzer {
private:
    std::ifstream sceneFile;
    std::unordered_map<std::string, Script> *scripts;
public:
    SceneAnalyzer(const std::filesystem::path& scenePath, std::unordered_map<std::string, Script>* scripts);
    void parseYamlDocument(YAML::Node doc, std::vector<GameObject>& gameObjects, bool& afterGameObject, const std::string& line);
    static std::string getFileId(const std::string& line);
    static std::map<int, GameObject> getGameObjectMap(const std::vector<GameObject>& gameObjects);
    std::vector<GameObject> analyzeScene();
    std::unordered_map<std::string, Script> getScripts();
};

#endif //TOOL_SCENEANALYZER_H
