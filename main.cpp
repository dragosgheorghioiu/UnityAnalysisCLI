#include <memory>
#include "Process.h"

int main(int argc, char** argv) {
    std::unique_ptr<Process> proc = std::make_unique<Process>(argc, argv);
    proc->run();
    return 0;
}
