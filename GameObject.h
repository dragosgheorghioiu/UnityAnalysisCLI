//
// Created by dregos on 12/7/23.
//

#ifndef TOOL_GAMEOBJECT_H
#define TOOL_GAMEOBJECT_H


#include <string>
#include <vector>

class GameObject {
private:
    std::string name;
    std::string id;
    std::vector<GameObject> children;
public:
    GameObject(const std::string& name,const std::string& id);
    std::string getName();
};


#endif //TOOL_GAMEOBJECT_H
