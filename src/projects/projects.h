#ifndef MOCKSTACHE_PROJECTS_H
#define MOCKSTACHE_PROJECTS_H

#include <vector>
#include <string>
#include <optional>

struct ProjectInfo {
    std::string name;
    std::optional<std::string> description;
};

bool check_if_projects_folder_exist();
bool create_projects_folder_if_not_exists();
int handle_projects_commands(std::vector<std::string> args);
int create_project(const ProjectInfo& projectInfo);

#endif //MOCKSTACHE_PROJECTS_H