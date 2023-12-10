#include "Process.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Not enough params provided (Ex: tool.exe path/to/input path/to/output)" << std::endl;
        return 0;
    }
    Process(argc, argv).run();
    return 0;
}
