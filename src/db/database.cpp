#include "database.h"
#include <sqlite3.h>
#include <iostream>
#include <sstream>

/**
 * @brief Internal static callback function used by sqlite3_exec for SELECT queries.
 * @details This function is crucial for processing the results of a SELECT statement.
 */
int SQLiteDB::callback(void* data, int argc, char** argv, char** azColName) {
    // Cast the void* data back to a pointer to our ResultSet
    ResultSet* result = static_cast<ResultSet*>(data);

    // Create a new Row (map) for the current result row
    Row row;
    for (int i = 0; i < argc; i++) {
        // Map column name (azColName[i]) to its value (argv[i])
        // If argv[i] is nullptr (NULL value), use an empty string.
        row[azColName[i]] = (argv[i] ? argv[i] : "");
    }

    // Add the fully populated row to the result set
    result->push_back(std::move(row));

    return 0; // Return 0 to continue processing rows
}

// --- Constructor / Destructor ---

SQLiteDB::SQLiteDB(const std::string& dbPath) : db(nullptr) {
    // sqlite3_open_v2 is generally safer and more flexible than sqlite3_open
    int rc = sqlite3_open_v2(
        dbPath.c_str(),
        &db,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, // Read/Write, Create if not exists, Thread-safe
        nullptr // VFS module name (nullptr uses default)
    );

    if (rc != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        db = nullptr;
    } else {
        std::cout << "Database successfully opened: " << dbPath << std::endl;
    }
}

SQLiteDB::~SQLiteDB() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        std::cout << "Database connection closed." << std::endl;
    }
}

// --- Public Methods ---

bool SQLiteDB::isOpen() const {
    return db != nullptr;
}

void SQLiteDB::setLastError(const std::string& msg) {
    lastError = msg;
    std::cerr << "SQL Error: " << msg << std::endl;
}

bool SQLiteDB::execute(const std::string& sql) {
    if (!isOpen()) {
        setLastError("Cannot execute: Database is not open.");
        return false;
    }

    char* zErrMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::stringstream ss;
        ss << "SQL error (" << rc << "): " << zErrMsg;
        setLastError(ss.str());
        sqlite3_free(zErrMsg); // Free the message allocated by sqlite3_exec
        return false;
    }

    return true;
}

bool SQLiteDB::query(const std::string& sql, ResultSet& result) {
    if (!isOpen()) {
        setLastError("Cannot query: Database is not open.");
        return false;
    }

    // Clear any previous results
    result.clear();

    char* zErrMsg = nullptr;
    // Pass a pointer to our result set as the 4th argument (data)
    int rc = sqlite3_exec(db, sql.c_str(), SQLiteDB::callback, &result, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::stringstream ss;
        ss << "SQL error (" << rc << "): " << zErrMsg;
        setLastError(ss.str());
        sqlite3_free(zErrMsg);
        return false;
    }

    return true;
}