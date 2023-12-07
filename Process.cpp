#include "Process.h"

Process::Process(int argc, char **argv) {
    args = std::make_unique<Args>(argc, argv);
}

void Process::populateScenePaths(std::filesystem::path &dirPath) {
    dirPath /= "Assets";
    dirPath /= "Scenes";
    try {
        if (std::filesystem::is_directory(dirPath)) {
            for (const auto &entry: std::filesystem::directory_iterator(dirPath)) {
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

void Process::run() {
    std::filesystem::path dirPath(args->getArgsList()[0]);
    populateScenePaths(dirPath);
    for (auto &scene: scenes) {
        SceneAnalyzer analyzer(scene.getScenePath());
        scene.setChildren(analyzer.analyzeScene());
    }
    for (auto &scene: scenes) {
        std::cout << scene.getScenePath() << std::endl;
        for (auto &gameObject: scene.getChildren()) {
            std::cout << gameObject.getName() << std::endl;
        }
    }
}
