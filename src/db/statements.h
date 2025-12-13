//
// Created by jocarrasco on 12/13/25.
//

#ifndef MOCKSTACHE_STATEMENTS_H
#define MOCKSTACHE_STATEMENTS_H
namespace SQL {
    const std::string CREATE_METADATA_TABLE =
        "CREATE TABLE IF NOT EXISTS metadata (\n"
        "   project_id INTEGER PRIMARY KEY, \n"
        "   name TEXT NOT NULL, \n"
        "   description TEXT DEFAULT ''\n"
        ");\n";

    const std::string ADD_PROJECT_METADATA(const std::string &name, const std::optional<std::string> &description) {
        std::string sql = "INSERT INTO metadata (name, description) VALUES (\"";

        // 2. Append the 'name' value
        sql += name;
        sql += "\", \"";

        // 3. Append the 'description' value (handle optional)
        if (description.has_value()) {
            sql += description.value();
        } else {
            // If optional is empty, insert an empty string or 'NULL'
            // For this example, we'll use an empty string ""
            sql += "";
        }

        // 4. Close the query
        sql += "\")";

        // Return the std::string object.
        return sql;
    }

    const std::string GET_PROJECT_METADATA(const std::string &name) {
        return "SELECT name, description FROM metadata WHERE name = " + name + ";";

    }
}
#endif //MOCKSTACHE_STATEMENTS_H