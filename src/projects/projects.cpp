#include "projects.h"
#include <filesystem>
#include <iostream>
#include <optional>

#include "../utils/utils.h"
#include "../db/database.h"
#include "../db/statements.h"

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
    const bool projects_folder_exists = check_if_projects_folder_exist();
    const std::string &operation(args[1]);

    if (operation.empty()) {
        return 1;
    }

    if (operation == "list") {
        if (!projects_folder_exists) {
            std::cout << "No projects stored found.";
            std::cout << std::endl;
            return 1;
        }
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
        if (!projects_folder_exists) {
            create_projects_folder_if_not_exists();
        }
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

    if (projectInfo.name.empty()) {
        std::cerr << "No valid project input";
        return 1;
    }

    if (projectInfo.description->empty()) {
        std::cerr << "No valid project description input";
        return 1;
    }

    const std::string target_file = get_projects_folder() + "/" + projectInfo.name + ".db";
    if (file_exists(target_file)) {
        std::cerr << "The project: " + target_file + " already exists.";
        return 1;
    }

    // Check if file with the same name exists
    try {
        create_file(target_file);
        std::cout << "Created project: " << target_file << std::endl;

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::optional<ProjectInfo> get_project_metadata(const std::string &project_name) {
    const std::string projects_folder = get_projects_folder();
    const std::string target_file = projects_folder + "/" + project_name + ".db";
    if (file_exists(target_file)) {
        SQLiteDB db(target_file);
        SQLiteDB::ResultSet metadataArr;
        if (db.query(SQL::GET_PROJECT_METADATA(project_name), metadataArr)) {
            if (metadataArr.empty()) {
                std::cout << "No project metadata for " << project_name << std::endl;
                return std::nullopt;
            } else {
                // NOTE(wip): Keep on developing this, is not yet finished.
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    } else {
        std::cerr << "No project metadata for " << project_name << std::endl;
        return std::nullopt;
    }
}

int saveMetadataToProject(const ProjectInfo& projectInfo) {
    const std::string projects_folder = get_projects_folder();
    const std::string target_file = projects_folder + "/" + projectInfo.name + ".db";

    try {
        SQLiteDB db(target_file);
        if (db.isOpen()) {
            db.execute(SQL::CREATE_METADATA_TABLE);
            db.execute(SQL::ADD_PROJECT_METADATA(projectInfo.name, projectInfo.description));
            return 0;
        } else {
            return 1;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
