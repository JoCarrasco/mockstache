#ifndef MOCKSTACHE_PROJECTS_H
#define MOCKSTACHE_PROJECTS_H

bool check_if_projects_folder_exist();
bool create_projects_folder_if_not_exists();
int handle_projects_commands(const char** remainingArgs);

#endif //MOCKSTACHE_PROJECTS_H