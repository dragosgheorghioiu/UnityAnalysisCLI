#include "GameObject.h"

GameObject::GameObject(const std::string& name, const std::string& id) {
    this->name = name;
    this->id = id;
    this->children = std::vector<std::string>();
}

std::vector<std::string> GameObject::getChildren() {
    return this->children;
}

std::string GameObject::getName() {
    return this->name;
}

void GameObject::addChild(const std::string& child) {
    this->children.emplace_back(child);
}
