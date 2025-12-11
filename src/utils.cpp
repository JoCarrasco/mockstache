#include <sys/stat.h>
#include <iostream>
#include <string>

bool directory_exists(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        // stat failed (e.g., directory does not exist or permission denied)
        return false;
    }
    // Check if the path points to a directory
    return (info.st_mode & S_IFDIR);
}

int create_directory_path(const std::string& path) {
 // 1. Determine the path for the config directory: ~/.config/stubmock
    size_t stubmock_end = full_db_path.find("/projects");
    std::string config_stubmock_dir = full_db_path.substr(0, stubmock_end);

    // 2. Determine the path for the projects directory: ~/.config/stubmock/projects
    size_t last_slash = full_db_path.find_last_of('/');
    std::string projects_dir = full_db_path.substr(0, last_slash);

    // --- Create ~/.config/stubmock ---
    if (!directory_exists(config_stubmock_dir)) {
        std::cout << "Creating directory: " << config_stubmock_dir << std::endl;
        if (mkdir(config_stubmock_dir.c_str(), 0755) != 0) {
            std::cerr << "Error creating " << config_stubmock_dir << ": " << strerror(errno) << std::endl;
            return -1;
        }
    }

    // --- Create ~/.config/stubmock/projects ---
    if (!directory_exists(projects_dir)) {
        std::cout << "Creating directory: " << projects_dir << std::endl;
        if (mkdir(projects_dir.c_str(), 0755) != 0) {
            std::cerr << "Error creating " << projects_dir << ": " << strerror(errno) << std::endl;
            return -1;
        }
    }

    return 0;
}
