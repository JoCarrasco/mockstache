#include <string>
#include <optional>
#include <sqlite3.h>
#include <sys/stat.h>
#include "utils.h"
#include "projects.h"

int handleProjectCommand(const char** remainingArgs) {
    std::string operation(remainingArgs[0]);
    std::string operationFirstValue(remainingArgs[1]);

    if (operation.empty()) {
        return 1;
    }



    sqlite3 *db; // Database connection object
    int rc = sqlite3_open("stubmock.db", &db);

    if (rc != SQLITE_OK) {
        sqlite3_close(db);
    }

    if (operation == "list") {

    }

}

bool check_if_project_folder_exists() {
    std:string path = getFullPath();
    std:string


}

std::string checkConfigFolder(const std::string &folderName) {
    std::string fullPath = getFullPath();
    if (directory_exists(fullPath + "/projects")) {
        std::cout << "Folders exists";
        std::endl;
    }
}

std::string getFullPath(const std::string &folderName) {
    const char* home_dir = std::getenv("HOME");
    if (!home_dir) {
        std::cerr << "Error: HOME environment variable not set. Cannot proceed." << std::endl;
        return '';
    }

    return std::string(home_dir) + "/.config/stubmock";
}
