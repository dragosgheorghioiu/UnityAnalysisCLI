#ifndef TOOL_GAMEOBJECT_H
#define TOOL_GAMEOBJECT_H


#include <string>
#include <vector>

class GameObject {
private:
    std::string name;
    std::string id;
    std::vector<std::string> children;
    std::string parent_id;
public:
    GameObject(const std::string& name, const std::string& id);
    std::string getName() const;
    std::vector<std::string > getChildren();
    void addChild(const std::string& child_id);
    int getId();
    std::string getParentId();
    void setParentId(const std::string& parentId);
};


#endif //TOOL_GAMEOBJECT_H
