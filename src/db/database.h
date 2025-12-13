//
// Created by jocarrasco on 12/13/25.
//

#ifndef MOCKSTACHE_DATABASE_H
#define MOCKSTACHE_DATABASE_H
#include <string>
#include <vector>
#include <map>
#include <sqlite3.h>

class SQLiteDB {
public:
    // Alias for a row of data: column name (string) -> value (string)
    using Row = std::map<std::string, std::string>;

    // Alias for the result set: a vector of rows
    using ResultSet = std::vector<Row>;

    /**
     * @brief Constructs a SQLiteDB object and attempts to open/create the database file.
     * @param dbPath The path to the SQLite database file.
     */
    SQLiteDB(const std::string& dbPath);

    /**
     * @brief Destructor. Closes the database connection.
     */
    ~SQLiteDB();

    // Disable copy/move constructors and assignment operators for safety
    SQLiteDB(const SQLiteDB&) = delete;
    SQLiteDB& operator=(const SQLiteDB&) = delete;

    /**
     * @brief Executes a non-query SQL statement (e.g., CREATE TABLE, INSERT, UPDATE, DELETE).
     * @param sql The SQL statement to execute.
     * @return true on success, false on error (error message printed to stderr).
     */
    bool execute(const std::string& sql);

    /**
     * @brief Executes a query SQL statement (e.g., SELECT) and returns the results.
     * @param sql The SQL query to execute.
     * @param result The ResultSet to store the query results in.
     * @return true on success, false on error (error message printed to stderr).
     */
    bool query(const std::string& sql, ResultSet& result);

    /**
     * @brief Checks if the database connection is open and valid.
     * @return true if the connection is open, false otherwise.
     */
    bool isOpen() const;

private:
    sqlite3* db; ///< Internal SQLite database handle.
    std::string lastError; ///< Stores the last error message.

    /**
     * @brief Internal static callback function used by sqlite3_exec for SELECT queries.
     */
    static int callback(void* data, int argc, char** argv, char** azColName);

    /**
     * @brief Utility function to update the last error message.
     */
    void setLastError(const std::string& msg);
};
#endif //MOCKSTACHE_DATABASE_H