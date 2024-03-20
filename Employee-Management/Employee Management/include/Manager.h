#ifndef manager_flag
#define manager_flag
#include "Employee.h"
#include "Utility.h"
#include "validate.h"

class Manager : public Employee {
public:
    Manager() = default;

    int getManagementExperience() const { return management_experience; }
    std::string getProjectTitle() const { return project_title; }

    void setManagementExperience(int managerExp) { management_experience = managerExp; }
    void setProjectTitle(const std::string& projectTitle) { project_title = projectTitle; }
    bool setExperienceUserInput();
    bool setProjectTileUserInput();

    void insertManager();
    void deleteManager();
    void updateManager();
    void viewManager();

    void describeManager();

    void action();

private:

    int management_experience{};
    std::string project_title{};
};

#endif