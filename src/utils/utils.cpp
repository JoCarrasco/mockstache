#include <cstring>
#include <filesystem>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <vector>

bool directory_exists(const std::string& path) {
    struct stat info{};
    if (stat(path.c_str(), &info) != 0) {
        // stat failed (e.g., directory does not exist or permission denied)
        return false;
    }
    // Check if the path points to a directory
    return (info.st_mode & S_IFDIR);
}

bool file_exists(const std::string& path) {
    struct stat info{};
    if (stat(path.c_str(), &info) != 0) {
        return false;
    }

    return (info.st_mode & S_IFREG);
}

bool create_folder_if_not_exists(const std::string& path) {
    // Check if folder exist
    struct stat info{};
    if (stat(path.c_str(), &info) != 0) {
       // Create the folder
        try {
            if (std::filesystem::create_directory(path)) {
                std::cout << "Successfully created directory: " << path << std::endl;
                return true;
            } else {
                std::cout << "Directory already exists: " << path << std::endl;
                return true;
            }
        } catch (const std::filesystem::filesystem_error& e) {
            // Catch other potential errors, like permission issues or invalid path format
            std::cerr << "Error creating directory " << path << ": " << e.what() << std::endl;
            return false;
        }
    } else {
        std::cout << "Directory already exists: " << path << std::endl;
        return true;
    }
}

std::string get_home_directory() {
    const char* home_dir = std::getenv("HOME");
    return home_dir;
}

std::vector<std::string> find_db_files(const std::filesystem::path& directory_path) {
    std::vector<std::string> db_files;

    if (!std::filesystem::exists(directory_path) || !std::filesystem::is_directory(directory_path)) {
        std::cerr << "Error: Directory does not exist or is not a directory: "
                  << directory_path << "\n";
        return db_files;
    }

    // Use a recursive iterator to search the directory and all its subdirectories
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory_path)) {

        // 1. Check if the current entry is a regular file
        //    (This prevents attempting to check the extension of directories or symlinks)
        if (entry.is_regular_file()) {

            // 2. Get the file's extension
            //    std::filesystem::path::extension() returns the extension (e.g., ".db")
            if (entry.path().extension() == ".db") {

                // 3. Add the full path to our list
                db_files.push_back(entry.path().string());
            }
        }
    }
    return db_files;
}
