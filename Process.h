#ifndef TOOL_PROCESS_H
#define TOOL_PROCESS_H


#include "Args.h"
#include <memory>
#include <filesystem>

class Process {
private:
    std::unique_ptr<Args> args;
public:
    Process(int argc, char **argv);
    static void printChildrenRecursively(const std::filesystem::path &dirPath, const int& i);
    void run();
};


#endif //TOOL_PROCESS_H
