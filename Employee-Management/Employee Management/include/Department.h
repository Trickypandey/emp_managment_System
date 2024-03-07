#ifndef dept_flag
#define dept_flag

#include <iostream>
#include <string>
#include "database.h"

class Department {
public:
    Department() = default;
    Department(Database& db)  {
        db_department = db;
    }

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getManagerId() const { return manager_id; }
    std::string getDescription() const { return description; }

    void setId(int ID) { id = ID; }
    void setName(const std::string& Name) { name = Name; }
    void setManagerId(int ManagerId) { manager_id = ManagerId; }
    void setDescription(const std::string& Description) { description = Description; }

    void insertDepartment();
    void deleteDepartment();
    void updateDepartment();
    void viewDepartment();
    void setIdFromUserInput();
    void setNameFromUserInput();
    void setManagerIdFromUserInput();
    void setDescriptionFromUserInput();

    void action();

private:

    Database db_department;
    int id {};
    std::string name {};
    int manager_id {};
    std::string description{};
};


#endif