#include "Args.h"

Args::Args(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        argList.emplace_back(argv[i]);
    }
}
void Args::printArgs() {
    for (auto &elem : argList) {
        std::cout << elem << "\n";
    }
}

std::vector<std::string> Args::getArgsList() {
    return argList;
}
