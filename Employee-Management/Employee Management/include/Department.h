#ifndef dept_flag
#define dept_flag
#include <iostream>
#include <string>
#include "database.h"
#include "Utility.h"
#include "Validate.h"
#include "controllers/departmentController.h"


class Department {
public:
    Department() = default;

    Department(int dept_id, const std::string& dept_name, int mgr_id, const std::string& dept_description)
        : id(dept_id), name(dept_name), manager_id(mgr_id), description(dept_description) {}


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
   
    bool setDidFromUserInput();
    bool setDNameFromUserInput();
    bool setDManagerIdFromUserInput();
    bool setDescriptionFromUserInput();

    void action();

private:

    int id{};
    std::string name{};
    int manager_id{};
    std::string description{};


    bool setDepartemntData() {
        if (!setDidFromUserInput() || !setDNameFromUserInput() || !setDManagerIdFromUserInput() ||
            !setDescriptionFromUserInput()) {
            std::cout << "Error setting Department data. Aborting insertion.\n";
            return false;
        }
        return true;
    }
};


#endif
