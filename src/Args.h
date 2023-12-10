#ifndef TOOL_ARGS_H
#define TOOL_ARGS_H


#include <iostream>
#include <string>
#include <vector>

/**
 * Class to handle command line arguments.
 */
class Args {
private:
    std::vector<std::string> argList;
public:
    Args(int argc, char** argv);
    std::vector<std::string> getArgsList();
    void printArgs();
};


#endif //TOOL_ARGS_H
