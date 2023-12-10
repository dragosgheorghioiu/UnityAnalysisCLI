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

std::filesystem::path Scene::getScenePath() const {
    return this->scenePath;
}

void Scene::setGameObjectMap(const std::map<int, GameObject>& map) {
    this->gameObjectMap = map;
}

std::map<int, GameObject> Scene::getGameObjectMap() const {
    return this->gameObjectMap;
}
