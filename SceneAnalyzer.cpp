#include "SceneAnalyzer.h"

SceneAnalyzer::SceneAnalyzer(const std::string &scenePath) {
    sceneFile = std::ifstream(scenePath);
}

void SceneAnalyzer::parseYamlDocument(YAML::Node doc, std::vector<GameObject>& gameObjects, bool& afterGameObject, const std::string& line) {
    if (doc["GameObject"]) {
        GameObject gameObject(doc["GameObject"]["m_Name"].as<std::string>(), SceneAnalyzer::getFileId(line));
        gameObjects.emplace_back(gameObject);
        afterGameObject = true;
        return;
    }

    if (doc["Transform"] && afterGameObject) {
        if (!doc["Transform"]["m_Children"])
            return;
        for (YAML::detail::iterator_value child: doc["Transform"]["m_Children"]) {
            (gameObjects.end() - 1)->addChild(child["fileID"].as<std::string>());
        }
        return;
    }

    afterGameObject = false;
}

std::string SceneAnalyzer::getFileId(const std::string &line) {
    std::stringstream ss(line);
    std::string res;
    getline(ss, res, '&');
    getline(ss, res, '&');
    return res;
}

std::vector<GameObject> SceneAnalyzer::analyzeScene() {
    std::vector<GameObject> gameObjects;
    std::string currentDocument;
    bool afterGameObject = false;
    std::string line;

    while (std::getline(sceneFile, line)) {
        if (line.starts_with("---")) {
            if (currentDocument.empty()) continue;
            YAML::Node doc = YAML::Load(currentDocument);
            SceneAnalyzer::parseYamlDocument(doc, gameObjects, afterGameObject, line);
            currentDocument = "";
        } else {
            currentDocument += line + "\n";
        }
    }
    return gameObjects;
}
