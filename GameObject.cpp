//
// Created by dregos on 12/7/23.
//

#include "GameObject.h"

GameObject::GameObject(const std::string& name, const std::string& id) {
    this->name = name;
    this->id = id;
    this->children = std::vector<GameObject>();
}

std::string GameObject::getName() {
    return this->name;
}
