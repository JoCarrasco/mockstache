#include <string>
#include <optional>

std::string getFullPath()

bool check_if_project_folder_exists()

struct ProjectInfo {
    std::string name;
    std::optional<std::string> description;
};
