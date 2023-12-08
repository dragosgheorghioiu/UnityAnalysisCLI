#include "GameObject.h"

GameObject::GameObject(const std::string& name, const std::string& id) {
    this->name = name;
    this->id = id;
    this->parent_id = parent_id;
    this->children = std::vector<std::string>();
}

std::vector<std::string> GameObject::getChildren() {
    return this->children;
}

std::string GameObject::getName() const {
    return this->name;
}

void GameObject::addChild(const std::string& child) {
    this->children.emplace_back(child);
}

int GameObject::getId() {
    return std::stoi(this->id);
}

std::string GameObject::getParentId() {
    return this->parent_id;
}

void GameObject::setParentId(const std::string& parentId) {
    this->parent_id = parentId;
}