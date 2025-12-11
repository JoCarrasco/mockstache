#include <iostream>
#include <vector>

int main(const int argc, const char * const argv[]) {
    if (argc < 1) {
        std::cout << "Not enough arguments provided." << std::endl;
    }

    const std::string firstCommand = argv[0];

    if (firstCommand.empty()) {
        std::cout << "Not enough arguments provided." << std::endl;
    }

    return EXIT_SUCCESS;
}


