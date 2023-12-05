#include "Process.h"

Process::Process(int argc, char **argv) {
    args = std::make_unique<Args>(argc, argv);
}

void Process::printChildrenRecursively(const std::filesystem::path &dirPath, const int &indents) {
    try {
        if (std::filesystem::is_directory(dirPath)) {
            for (const auto &entry: std::filesystem::directory_iterator(dirPath)) {
                for (int i = 0; i < indents; i++) {
                    std::cout << "    ";
                }
                std::cout << entry.path().filename() << std::endl;
                if (entry.is_directory()) {
                    printChildrenRecursively(entry.path(), indents + 1);
                }
            }
        } else {
            std::cout << "The provided directory is not a path" << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
    }
}

void Process::run() {
    printChildrenRecursively(args->getArgsList()[0], 0);
}