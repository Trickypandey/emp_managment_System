#include "../include/database.h"
#include<string>
#include <vector>
#include <iostream>


bool Database::open() {
    if (sqlite3_open(dbName.c_str(), &db) == SQLITE_OK) {

        if (!createTables()) {
            return false;
        }

        return true;
    }
    else {
        setError("Failed to open database");
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

void Database::close() {
    if (db) {
        std::cout << "DB closed\n";
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::executeQuery(const std::string& query) {
    char* errMsg = nullptr;


    int rc = sqlite3_exec(db, query.c_str(), NULL, 0, &errMsg);

    if (rc != SQLITE_OK) {
        setError(errMsg);
        sqlite3_free(errMsg);
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
    if (rc != SQLITE_OK) {
        setError(errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}


int Database::callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; ++i) {
        std::cout<< azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
    return 0;
}

void Database::setError(const std::string& errorMessage) {
    Error = errorMessage;
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
