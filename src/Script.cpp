#include "Script.h"

Script::Script(const std::filesystem::path& name, const std::filesystem::path& projectRoot) : name(name), projectRoot(projectRoot){
    try {
        loadGuid();
    } catch (const std::exception &e) {
        std::cout << "Error loading guid for script " << name << std::endl;
        std::cout << e.what() << std::endl;
    }
}

void Script::loadGuid() {
    YAML::Node doc = YAML::LoadFile(name.string() + ".meta");
    guid = doc["guid"].as<std::string>();
}

std::string Script::getGuid() const {
    return guid;
}

std::string Script::getRelativePath() const {
    return std::filesystem::relative(name, projectRoot).generic_string();
}