//
// Created by dregos on 12/7/23.
//

#ifndef TOOL_SCENE_H
#define TOOL_SCENE_H


#include <vector>
#include <string>
#include <filesystem>
#include "GameObject.h"

class Scene {
private:
    std::vector<GameObject> children;
    std::filesystem::path scenePath;
public:
    Scene(const std::string& path, const std::vector<GameObject>& children);
    std::vector<GameObject> getChildren();
    std::filesystem::path getScenePath();
    void setChildren(const std::vector<GameObject>& vector);
};


#endif //TOOL_SCENE_H
