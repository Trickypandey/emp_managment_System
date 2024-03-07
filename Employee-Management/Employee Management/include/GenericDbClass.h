#pragma once
#include "../sqlite/sqlite3.h"
#include<string>
#include<vector>
class DB {

    DB() = default;
    DB(const std::string& db) :dbName(db) {}

    ~DB() {
        //close();
    }
private:
    sqlite3* db;
    std::string dbName{};
    std::string Error{};

    //static int callback(void* data, int argc, char** argv, char** azColName);
};