#include "projects.h"
#include <filesystem>
#include <iostream>
#include "../utils/utils.h"

std::string get_projects_folder() {
    const std::string home = get_home_directory();
    const std::string targetDir = home + "/.config/mockstache/projects";
    return targetDir;
}

bool check_if_projects_folder_exist() {
    return directory_exists(get_projects_folder());
}

bool create_projects_folder_if_not_exists() {
    if (check_if_projects_folder_exist()) {
        try {
            create_folder_if_not_exists(get_projects_folder());
            return true;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    } else {
        create_folder_if_not_exists(get_projects_folder());
        return true;
    }
}

int handle_projects_commands(const std::vector<std::string> args) {
    if (check_if_projects_folder_exist()) {
        return 1;
    }

    const std::string &operationFirstValue(args[1]);

    if (operationFirstValue.empty()) {
        return 1;
    }

    if (operationFirstValue == "list") {
        // list all *.db files inside the "projects" folder

        const std::string projectsFolder = get_projects_folder();
        const std::vector<std::string> dbFiles = find_db_files(projectsFolder);
        // Pretty print the file names without the .db

        if (dbFiles.empty()) {
            std::cout << "No projects stored found.";
            std::cout << std::endl;
            return 0;
        }

        for (const auto& dbFile : dbFiles) {
            std::cout << dbFile << std::endl;
        }
    }

    return 0;
}
