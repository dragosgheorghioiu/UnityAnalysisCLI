#ifndef TOOL_SCRIPT_H
#define TOOL_SCRIPT_H

#include <iostream>
#include <string>
#include <filesystem>
#include "yaml-cpp/yaml.h"

class Script {
private:
   std::string guid;
   std::filesystem::path name;
   std::filesystem::path projectRoot;
public:
    Script(const std::filesystem::path& name, const std::filesystem::path& projectRoot);
    std::string getGuid() const;

    void loadGuid();

    std::string getRelativePath() const;
};


#endif //TOOL_SCRIPT_H
