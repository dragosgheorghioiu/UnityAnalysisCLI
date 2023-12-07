#include "SceneAnalyzer.h"

SceneAnalyzer::SceneAnalyzer(const std::string &scenePath) {
    sceneFile = std::ifstream(scenePath);
}

std::string getFileId(const std::string& line) {
    std::stringstream ss(line);
    std::string res;
    getline(ss, res, '&');
    getline(ss, res, '&');
    return res;
}

std::vector<GameObject> SceneAnalyzer::analyzeScene() {
    std::vector<GameObject> gameObjects;
    std::string currentDocument;

    std::string line;
    while (std::getline(sceneFile, line)) {
        if (line.starts_with("---")) {
            if (currentDocument.empty()) continue;
            YAML::Node doc = YAML::Load(currentDocument);
            if (doc["GameObject"]) {
                gameObjects.emplace_back(doc["GameObject"]["m_Name"].as<std::string>(), getFileId(line));
            }
            currentDocument = "";

        } else {
            currentDocument += line + "\n";
        }
    }
    return gameObjects;
}
