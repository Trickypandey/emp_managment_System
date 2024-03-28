#include "../include/database.h"


using logs::Log;

int Database::rows = 0;
bool Database::open(std::filesystem::path dbPath) {

    if (sqlite3_open(dbPath.string().c_str(), &db) == SQLITE_OK) {

        if (!createTables()) {
            return false;
        }

        std::string pragmaQuery = { "PRAGMA foreign_keys = ON;" };
        executeQuery(pragmaQuery);

        return true;
    }
    else {
        std::string_view err = { "Failed to open database" };
        setError(err);
        Log::getInstance().Error("Failed to open database.");
        return false;
    }
}

bool Database::createTables() {

    const char* sql = "CREATE TABLE IF NOT EXISTS Employee ("
        "id INTEGER PRIMARY KEY,"
        "firstname VARCHAR,"
        "lastname VARCHAR,"
        "dob DATE,"
        "mobile VARCHAR,"
        "email VARCHAR,"
        "address VARCHAR,"
        "gender VARCHAR CHECK (gender IN ('Male', 'Female', 'Other')),"
        "doj DATE,"
        "w_location VARCHAR,"
        "manager_id INTEGER,"
        "department_id INTEGER,"
        "FOREIGN KEY (department_id) REFERENCES Department(id),"
        "FOREIGN KEY (manager_id) REFERENCES Employee(id));";

    if (!executeQuery(sql))
    {
        return false;
    }

    const char* sql2 = "CREATE TABLE IF NOT EXISTS Department ("
        "id INTEGER PRIMARY KEY,"
        "name VARCHAR,"
        "manager_id INTEGER,"
        "description VARCHAR,"
        "FOREIGN KEY (manager_id) REFERENCES Employee(id))";


    if (!executeQuery(sql2))
    {
        return false;
    }



    const char* sql3 = "CREATE TABLE IF NOT EXISTS Engineer ("
        "id INTEGER PRIMARY KEY,"
        "programming_language VARCHAR,"
        "specialization VARCHAR,"
        "FOREIGN KEY (id) REFERENCES Employee(id))";

    if (!executeQuery(sql3))
    {
        return false;
    }


    const char* sql4 = "CREATE TABLE IF NOT EXISTS Manager ("
        "id INTEGER PRIMARY KEY,"
        "management_experience INTEGER,"
        "project_title VARCHAR,"
        "FOREIGN KEY (id) REFERENCES Employee(id))";


    if (!executeQuery(sql4))
    {
        return false;
    }


    const char* sql5 = "CREATE TABLE IF NOT EXISTS Salary ("
        "id INTEGER PRIMARY KEY,"
        "amount INTEGER,"
        "base_salary INTEGER,"
        "bonus INTEGER,"
        "FOREIGN KEY (id) REFERENCES Employee(id))";

    if (!executeQuery(sql5))
    {
        return false;
    }


    return true;
}

std::string Database::generateCreateTableQuery() {
    std::string tableName;
    std::cout << "Enter table name: ";
    std::cin >> tableName;

    std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
    std::vector<std::string> columns;

    // Input column details from the user
    char choice;
    do {
        std::string columnName, columnType, constraints;
        std::cout << "Enter column name: ";
        std::cin >> columnName;
        std::cout << "Enter column type: ";
        std::cin >> columnType;

        // Input constraints (if any)
        std::cout << "Enter column constraints (e.g., PRIMARY KEY, FOREIGN KEY): ";
        std::cin.ignore();
        std::getline(std::cin, constraints);

        // Append column name, type, and constraints to the SQL query
        columns.push_back(columnName + " " + columnType + " " + constraints);

        std::cout << "Add another column? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Concatenate column details to form the final SQL query
    for (size_t i = 0; i < columns.size(); ++i) {
        sql += columns[i];
        if (i < columns.size() - 1) {
            sql += ",";
        }
    }
    sql += ");";

    return sql;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        Log::getInstance().Info("Database Closed.");
    }
}

bool Database::executeQuery(const std::string& query) {

    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query.c_str(), NULL, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::string_view err = { errMsg };
        setError(err);
        Log::getInstance().Error(errMsg);
        //sqlite3_free(errMsg);
        return false;
    }

    return true;
}


std::string Database::getError() const {
    return Error;
}

bool Database::executeQueryCallback(const std::string& query) {
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);
    std::cout << rows << " rows returned \n\n";
    rows = 0;
    if (rc != SQLITE_OK) {
        setError(errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}
int Database::getRow() {
    return rows;
}

int Database::callback(void* data, int argc, char** argv, char** azColName) {
    ++rows;
    int colWidth = 22;
    int length;
    std::cout << "----------------------------------------" << std::endl;
    for (int i = 0; i < argc; ++i) {
        length = strlen(azColName[i]) - 2;
        std::cout << " " << azColName[i] << std::setw(colWidth - length) << ": " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << "----------------------------------------" << std::endl;
    return 0;
}

void Database::setError(const std::string_view& errorMessage) {
    Error = errorMessage;
}



bool Database::executeQueryRows(const std::string& query) {
    char* errMsg = nullptr;
    rows = 0;
    int rc = sqlite3_exec(db, query.c_str(), callbackRows, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::string_view err = { errMsg };
        setError(err);
        //sqlite3_free(errMsg);
        return false;
    }
    return true;
}

int Database::callbackRows(void* data, int argc, char** argv, char** azColName) {
    ++rows;
    return 0;
}

void Database::export_to_csv(const std::string& table, const std::filesystem::path& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string query = "SELECT * FROM " + table + ";";
    if (!Database::getInstance().executeQuery(query)) {
        std::cerr << "Failed to execute query." << std::endl;
        return;
    }

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    int columns = sqlite3_column_count(stmt);
    for (int i = 0; i < columns; ++i) {
        file << sqlite3_column_name(stmt, i);
        if (i < columns - 1)
            file << ",";
    }
    file << "\n";

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        for (int i = 0; i < columns; ++i) {
            if (sqlite3_column_text(stmt, i)) {
                file << sqlite3_column_text(stmt, i);
            }
            if (i < columns - 1)
                file << ",";
        }
        file << "\n";
    }

    if (rc != SQLITE_DONE) {
        std::cout << getError() << "\n\n";
    }
    else {
        Log::getInstance().Info("Database Exported.");
    }
    sqlite3_finalize(stmt);
}


void Database::createTableQuery() {

    std::string tableName;
    std::cout << "Enter table name: ";
    std::cin >> tableName;

    std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
    std::vector<std::string> columns;

    char choice;
    do {
        std::string columnName, columnType, constraints;
        std::cout << "Enter column name: ";
        std::cin >> columnName;
        std::cout << "Enter column type: ";
        std::cin >> columnType;

        std::cout << "Enter column constraints : ";
        std::cin.ignore();
        std::getline(std::cin, constraints);

        columns.push_back(columnName + " " + columnType + " " + constraints);

        std::cout << "Add another column? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    for (int i = 0; i < columns.size(); ++i) {
        sql += columns[i];
        if (i < columns.size() - 1) {
            sql += ",";
        }
    }
    sql += ");";

    if (executeQuery(sql)) {
        Log::getInstance().Info(tableName, " created.");
    }

}

void Database::showTables() {

    std::string showQuery = " SELECT name FROM sqlite_schema ;";
    if (!executeQueryCallback(showQuery))
        std::cout << getError() << "\n\n";
    else {

    }
        Log::getInstance().Info("Show table Query Fetched.");

}

void Database::deleteTableQuery() {

    system("cls");
    int input;
    std::cout << "Enter 1 to Drop table or Enter 2 to Delete data within the table:";
    std::cin >> input;

    std::string deleteQuery;
    std::string tableName;

    switch (input) {
    case 1:
        std::cout << "Enter Table Name to Drop: ";
        std::cin >> tableName;

        deleteQuery = "DROP TABLE " + tableName + ";";

        if (executeQuery(deleteQuery)) {
            std::cout << "Table Dropped Succesfully ! \n\n";
            Log::getInstance().Info(tableName, " Dropped.");

        }
        else
            std::cout << Database::getInstance().getError() << "\n\n";

        break;

    case 2:
        std::cout << "Enter Table Name to Delete: ";
        std::cin >> tableName;
        deleteQuery = "DELETE FROM " + tableName + ";";

        if (executeQuery(deleteQuery)) {
            std::cout << "Table Deleted Succesfully ! \n\n";
            Log::getInstance().Info(tableName, " Deleted.");
        }
        else
            std::cout << Database::getInstance().getError() << "\n\n";

        break;

    default:
        std::cout << "Wrong Input..!\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }

}

void Database::useSqlQuery()
{

    std::string sqlQuery;

    std::cout << "Enter sql query : ";
    std::cin.ignore();
    std::getline(std::cin, sqlQuery);

    for (int i = 0; i < sqlQuery.size(); i++) {
        sqlQuery[i] = std::tolower(sqlQuery[i]);
    }

    size_t pos = sqlQuery.find("select");


    if (pos == 0) {
        if (executeQueryCallback(sqlQuery)) {
            std::cout << "SQL Query Completed Successfully ! \n\n";
            Log::getInstance().Info(sqlQuery, " : Executed.");
        }
        else
            std::cout << getError() << "\n";
    }
    else {
        if (executeQuery(sqlQuery)) {
            std::cout << "SQL Query Completed Successfully ! \n\n";
            Log::getInstance().Info(sqlQuery, " : Executed.");
        }
        else
            std::cout << getError() << "\n";
    }

}


void describeTable(const std::string& tableName) {
    std::string query = "pragma table_info('" + tableName + "');";
    if (!Database::getInstance().executeQueryCallback(query)) {
        std::cout << Database::getInstance().getError() << std::endl;
    }
    else {
        Log::getInstance().Info("Department Described.");
    }
}

bool Database::isIdExist(int id, const std::string& tableName) {
    std::string query = "SELECT id FROM " + tableName + " WHERE id = " + std::to_string(id) + ";";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        setError("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
        return false;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {

        sqlite3_finalize(stmt);
        return true;
    }
    else if (rc == SQLITE_DONE) {

        sqlite3_finalize(stmt);
        return false;
    }
    else {

        setError("SQL error: " + std::string(sqlite3_errmsg(db)));
        sqlite3_finalize(stmt);
        return false;
    }
}