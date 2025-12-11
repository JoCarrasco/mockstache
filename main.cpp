#include <iostream>
#include <optional>
#include <string>

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName) {
    cerr << (const char*)data << ": ";
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    cout << endl;
    return 0;
}

void displayHelp(const std::string& appName) {
    std::cout << "Usage: " << appName << " [OPTIONS]" << std::endl;
    std::cout << std::endl;
    std::cout << "This simple CLI application adds two numbers." << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -a <number>, --num1 <number>   The first number for addition." << std::endl;
    std::cout << "  -b <number>, --num2 <number>   The second number for addition." << std::endl;
    std::cout << "  -h, --help                     Display this help message and exit." << std::endl;
    std::cout << std::endl;
}

bool check_command_structure(int argc, char** argv) {
    const int EXPECTED_ARGS = 4; // Expected arguments: ./stubmock project add

    // Check if the exact number of arguments is provided
    if (argc < EXPECTED_ARGS) {
        return false;
    }

    // Convert arguments to std::string for easier comparison
    std::string arg1(argv[1]);
    std::string arg2(argv[2]);
    std::string arg3(argv[3]);
}


int main(int argc, char* argv[])
{
   if (argc < 2) {
        displayHelp(argv[0]);
        // Exit with an error code if required arguments are missing, but no flags are provided
        return 1;
    }


    if (check_command_structure(argc, argv)) {
        std::string p1 = argv[0];
        std::string p2 = argv[1];
        std::string p3 = argv[2];

        if (p1 == "project")
    }

}
