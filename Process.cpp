#include "Process.h"

Process::Process(int argc, char **argv) {
    args = std::make_unique<Args>(argc, argv);
}

void Process::searchForScriptsInDir(const std::filesystem::path &dirPath) {
    for (const auto &entry: std::filesystem::directory_iterator(dirPath)) {
        if (std::filesystem::is_directory(entry.path())) {
            searchForScriptsInDir(entry.path());
            continue;
        }
        if (entry.path().filename().extension() == ".cs") {
            Script script(entry.path(), args->getArgsList()[0]);
            scripts.emplace(script.getGuid(), script);
        }
    }
}

void Process::populateAllScripts(std::filesystem::path dirPath) {
    dirPath /= "Assets";
    dirPath /= "Scripts";
    try {
        if (std::filesystem::is_directory(dirPath)) {
            searchForScriptsInDir(dirPath);
        } else {
            std::cout << "The provided directory is not a valid Unity Project." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
    }
}

void Process::populateScenePaths(std::filesystem::path inputPath) {
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
            std::cerr << "[ERROR]: The provided directory is not a valid Unity Project." << std::endl;
            exit(1);
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
    }
}

void Process::analyzeProject() {
    for (auto &scene : scenes) {
        SceneAnalyzer analyzer(scene.getScenePath(), &scripts);
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

void Process::dumpSceneHeirarchy() {
    std::filesystem::path outputPath(args->getArgsList()[1]);
    for (auto &scene : scenes) {
        std::ofstream file = std::ofstream(outputPath / (scene.getScenePath().filename().string() + ".dump"), std::ios::trunc);
        printSceneHierarchy(scene, file);
        file.close();
    }
}

void Process::createUnusedScriptCSV(const std::filesystem::path &outputPath) {
    std::ofstream file = std::ofstream(outputPath / "UnusedScripts.csv", std::ios::trunc);
    file << "Relative Path,GUID\n";
    for (auto &[guid, script] : scripts) {
        file << script.getRelativePath() << "," << script.getGuid() << "\n";
    }
    file.close();
}

void Process::run() {
    std::filesystem::path inputPath(args->getArgsList()[0]);
    populateScenePaths(inputPath);
    populateAllScripts(inputPath);
    createOutputDirectory();
    analyzeProject();
    dumpSceneHeirarchy();
    createUnusedScriptCSV(args->getArgsList()[1]);
}
