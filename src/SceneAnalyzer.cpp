#include "SceneAnalyzer.h"

SceneAnalyzer::SceneAnalyzer(const std::filesystem::path &scenePath, std::unordered_map<std::string, Script> *scripts) {
    sceneFile = std::ifstream(scenePath);
    this->scripts = scripts;
}

void SceneAnalyzer::parseYamlDocument(YAML::Node doc, std::vector<GameObject>& gameObjects, bool& afterGameObject, const std::string& line) {
    if (doc["MonoBehaviour"]) {
        if (!doc["MonoBehaviour"]["m_Script"]) return;
        std::string guid = doc["MonoBehaviour"]["m_Script"]["guid"].as<std::string>();
        auto it = scripts->find(guid);
        if (it == scripts->end()) return;
        scripts->erase(it);
    }
    if (doc["GameObject"]) {
        GameObject gameObject(doc["GameObject"]["m_Name"].as<std::string>(), SceneAnalyzer::getFileId(line));
        gameObjects.emplace_back(gameObject);
        afterGameObject = true;
        return;
    }

    if (doc["Transform"] && afterGameObject) {
        afterGameObject = false;
        if (doc["Transform"]["m_Father"])
            (gameObjects.end() - 1)->setParentId(doc["Transform"]["m_Father"]["fileID"].as<std::string>());
        else (gameObjects.end() - 1)->setParentId("0");
        if (!doc["Transform"]["m_Children"])
            return;
        for (YAML::detail::iterator_value child: doc["Transform"]["m_Children"]) {
            (gameObjects.end() - 1)->addChild(child["fileID"].as<std::string>());
        }
        return;
    }
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

std::map<int, GameObject>
SceneAnalyzer::getGameObjectMap(const std::vector<GameObject> &gameObjects) {
    std::map<int, GameObject> gameObjectMap;
    for (GameObject gameObject: gameObjects) {
        gameObjectMap.emplace(gameObject.getId(), gameObject);
    }
    return gameObjectMap;
}
