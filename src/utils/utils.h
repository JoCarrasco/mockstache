//
// Created by jocarrasco on 12/11/25.
//

#ifndef MOCKSTACHE_UTILS_H
#define MOCKSTACHE_UTILS_H
#include <string>
#include <vector>

std::string get_home_directory();
bool directory_exists(const std::string& path);
bool file_exists(const std::string& path);
bool create_folder_if_not_exists(const std::string& path);

int create_file(const std::string& full_file_path);
std::vector<std::string> find_db_files(const std::filesystem::path& directory_path);
#endif //MOCKSTACHE_UTILS_H