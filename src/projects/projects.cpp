#include "projects.h"
#include <filesystem>
#include <iostream>
#include <optional>

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
    if (check_if_projects_folder_exist() == false) {
        std::cout << "No projects found in " + get_projects_folder() + ".";
        return 0;
    }

    const std::string &operation(args[1]);

    if (operation.empty()) {
        return 1;
    }

    if (operation == "list") {
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
    } else if (operation == "add") {
        // Compound object
        const std::string &project_name = args[2];
        const std::string &project_description = args[3];
        const ProjectInfo &project_info = {
            project_name,
            project_description,
        };

         return create_project(project_info);
    }

    return 0;
}

int create_project(const ProjectInfo& projectInfo) {
    if (projectInfo.name.empty() || projectInfo.name.back() != '.' || projectInfo.name.back() != '/') {
        std::cerr << "No valid project input";
        return 1;
    }

    if (projectInfo.description->empty() || projectInfo.description->back() != '.') {
        std::cerr << "No valid project description input";
        return 1;
    }

    const std::string target_file = get_projects_folder() + "/" + projectInfo.name;
    if (file_exists(target_file)) {
        std::cerr << "The project: " + target_file + " already exists.";
        return 1;
    }
}
