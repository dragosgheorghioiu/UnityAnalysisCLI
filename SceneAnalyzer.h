//
// Created by dregos on 12/7/23.
//

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
    std::vector<GameObject> analyzeScene();
};


#endif //TOOL_SCENEANALYZER_H
