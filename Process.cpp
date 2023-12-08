#include "Process.h"

Process::Process(int argc, char **argv) {
    args = std::make_unique<Args>(argc, argv);
}

void Process::populateScenePaths(std::filesystem::path &inputPath) {
    inputPath /= "Assets";
    inputPath /= "Scenes";
    try {
        if (std::filesystem::is_directory(inputPath)) {
            for (const auto &entry: std::filesystem::directory_iterator(inputPath)) {
                if (entry.path().filename().extension() == ".unity") {
                    scenes.emplace_back(entry.path().string(), std::vector<GameObject>());
                }
            }
        } else {
            std::cout << "The provided directory is not a valid Unity Project." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
    }
}

void Process::populateSceneChildren() {
    for (auto &scene : scenes) {
        SceneAnalyzer analyzer(scene.getScenePath());
        std::vector<GameObject> children = analyzer.analyzeScene();
        scene.setChildren(children);
        scene.setGameObjectMap(SceneAnalyzer::getGameObjectMap(children));
    }
}

void Process::printChild(const std::string &child, const std::map<int, GameObject> &gameObjectMap, const int &depth, std::ofstream &fout) {
    for (int i = 0; i < depth; i++) {
        fout << "--";
    }
    GameObject gameObject = gameObjectMap.at(std::stoi(child));
    fout << gameObject.getName() << "\n";
    for (auto &item : gameObject.getChildren()) {
        printChild(item, gameObjectMap, depth + 1, fout);
    }
}

void Process::createOutputDirectory() {
    std::filesystem::path inputPath(args->getArgsList()[1]);
    try {
        std::filesystem::create_directory(inputPath);
        }
    catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
    }
}

void Process::printSceneHierarchy(const Scene &scene, std::ofstream &fout) {
    std::map<int, GameObject> gameObjectMap = scene.getGameObjectMap();
    for (auto &[id, gameObject] : gameObjectMap) {
    if (gameObject.getParentId() != "0") continue;
        fout << gameObject.getName() << "\n";
        for (auto &child : gameObject.getChildren()) {
            printChild(child, gameObjectMap, 1, fout);
        }
    }
}

void Process::run() {
    std::filesystem::path inputPath(args->getArgsList()[0]);
    createOutputDirectory();
    std::filesystem::path outputPath(args->getArgsList()[1]);
    populateScenePaths(inputPath);
    populateSceneChildren();
    for (auto &scene : scenes) {
        std::ofstream file = std::ofstream(outputPath / (scene.getScenePath().filename().string() + ".dump"), std::ios::trunc);
        printSceneHierarchy(scene, file);

        // delete last newline to match output example
        long pos = file.tellp();
        file.seekp(pos - 1);
        file.write("", 1);

        file.close();
    }
}
