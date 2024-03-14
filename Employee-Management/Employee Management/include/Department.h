#ifndef dept_flag
#define dept_flag

#include <iostream>
#include <string>
#include "database.h"
#include "Utility.h"
#include "Validate.h"

class Department {
public:
    Department() = default;
    

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

    int id {};
    std::string name {};
    int manager_id {};
    std::string description{};
};


#endif