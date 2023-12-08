#ifndef TOOL_SCENEANALYZER_H
#define TOOL_SCENEANALYZER_H

#include "GameObject.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

class SceneAnalyzer {
private:
    std::ifstream sceneFile;
public:
    explicit SceneAnalyzer(const std::string& scenePath);
    static void parseYamlDocument(YAML::Node doc, std::vector<GameObject>& gameObjects, bool& afterGameObject, const std::string& line);
    static std::string getFileId(const std::string& line);
    std::vector<GameObject> analyzeScene();
    static std::map<int, GameObject> getGameObjectMap(const std::vector<GameObject>& gameObjects);
};


#endif //TOOL_SCENEANALYZER_H
