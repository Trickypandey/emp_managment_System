#pragma once
#include "../sqlite/sqlite3.h"
#include<string>
#include<vector>

class Database {
public:
    sqlite3* db{};

    bool open(std::string);
    bool createTables();
    std::string generateCreateTableQuery();
    void close();

    static Database& getInstance() {
        static Database DB;
        return DB;
    }

    bool executeQuery(const std::string& query);
    bool executeQueryCallback(const std::string& query);
    std::string getError() const;
    int getRow();
    void setError(const std::string& errorMessage);
    bool isIdExist(int id, const std::string& tableName);

private:
    Database() {}
    ~Database() {
        //sqlite3_close(db);
        close();
    }
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    std::string dbName{};
    std::string Error{};
    static int rows;
    static int callback(void* data, int argc, char** argv, char** azColName);

};


