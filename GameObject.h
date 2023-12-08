#ifndef TOOL_GAMEOBJECT_H
#define TOOL_GAMEOBJECT_H


#include <string>
#include <vector>

class GameObject {
private:
    std::string name;
    std::string id;
    std::vector<std::string> children;
public:
    GameObject(const std::string& name,const std::string& id);
    std::string getName();
    std::vector<std::string > getChildren();
    void addChild(const std::string& child_id);
};


#endif //TOOL_GAMEOBJECT_H
