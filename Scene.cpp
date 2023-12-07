#include "Scene.h"

Scene::Scene(const std::string& path, const std::vector<GameObject>& children) {
    this->scenePath = path;
    this->children = children;
}

std::vector<GameObject> Scene::getChildren() {
    return this->children;
}

void Scene::setChildren(const std::vector<GameObject>& vector) {
    this->children = vector;
}

std::filesystem::path Scene::getScenePath() {
    return this->scenePath;
}
