#include <iostream>
#include <vector>
#include "projects/projects.h"

int process_arguments(int argc, const std::vector<std::string> &args);
std::vector<std::string> clean_args(int argc, const char ** argv);

int main(const int argc, const char **argv) {
    if (argc == 1) {
        std::cout << "Not enough arguments provided." << std::endl;
        return 1;
    }

    return process_arguments(argc, clean_args(argc, argv));
}

std::vector<std::string> clean_args(const int argc, const char ** argv) {
    const char **start_it = argv + std::min(1, argc);
    const char **end_it = argv + argc;
    std::vector<std::string> cleaned_args(start_it, end_it);
    return cleaned_args;
}

int process_arguments(const int argc, const std::vector<std::string> &args) {
    if (argc < 3) {
        std::cout << "Not enough arguments provided." << std::endl;
    }

    const std::string &firstCommand = args[0];

    if (firstCommand.empty()) {
        std::cout << "Not enough arguments provided." << std::endl;
    }

    if (firstCommand == "projects") {
        return handle_projects_commands(args);

    }

    return EXIT_SUCCESS;
}
