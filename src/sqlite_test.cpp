#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;
    char* errMsg = nullptr;

    // Open or create the database
    if (sqlite3_open("test.db", &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    std::cout << "Database connected successfully!\n";

    // Create a test table
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS TestTable (id INTEGER PRIMARY KEY, value TEXT);";
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created successfully!\n";
    }

    // Insert a test value
    const char* insertSQL = "INSERT INTO TestTable (value) VALUES ('Hello SQLite!');";
    if (sqlite3_exec(db, insertSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error inserting data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Data inserted successfully!\n";
    }

    // Retrieve and display the inserted value
    const char* selectSQL = "SELECT id, value FROM TestTable;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

            std::cout << "Retrieved row -> ID: " << id << ", Value: " << value << std::endl;
        }
    } else {
        std::cerr << "Error retrieving data.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    std::cout << "Database closed.\n";

    return 0;
}