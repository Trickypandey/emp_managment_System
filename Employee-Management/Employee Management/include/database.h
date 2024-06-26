#pragma once
#include "../sqlite/sqlite3.h"
#include "../sqlite/sqlite3.h"
#include<string>
#include<vector>
#include <filesystem>
#include "log.h"
#include<string>
#include <iostream>
#include <iomanip>

class Database {
public:
    sqlite3* db{};

    bool open(std::filesystem::path);
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
    bool executeQueryRows(const std::string& query);
    void setError(const std::string_view& errorMessage);
    bool isIdExist(int id, const std::string& tableName);
    void export_to_csv(const std::string& table, const std::filesystem::path& filename);
    void describeTable(const std::string& tableName);
    void createTableQuery();
    void showTables();
    void deleteTableQuery();
    void useSqlQuery();
    void pragmeSwitch(bool pragmaSwitch);

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
    static int callbackRows(void* data, int argc, char** argv, char** azColName);

};


