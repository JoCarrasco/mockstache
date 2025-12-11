#include <iostream>
#include <vector>

#include "projects/projects.h"

int main(const int argc, const char **argv) {
    if (argc < 3) {
        std::cout << "Not enough arguments provided." << std::endl;
    }

    const std::string firstCommand = argv[1];
    const std::string secondCommand = argv[2];

    if (firstCommand.empty()) {
        std::cout << "Not enough arguments provided." << std::endl;
    }

    if (firstCommand == "projects") {
        handle_projects_commands(argv);
    }

    return EXIT_SUCCESS;
}


