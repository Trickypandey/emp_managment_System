#include "../include/Manager.h"

using namespace Utility;
bool Manager::setExperienceUserInput() {

    if (auto input = getInput<int>("Enter Manager's Experience in years: ", "Invalid input. Please enter a non-negative integer.", Validation::validateInt); input.has_value()) {
        setManagementExperience(input.value());
        return true;
    }
    return false;
}

bool Manager::setProjectTileUserInput() {
    
    if (auto input = getInput<std::string>("Enter Manager's Project Title: ", "Invalid input. Please try again.",[](const std::string& str) { return !str.empty() && Validation::validateString(str); }); input.has_value()) {
        setProjectTitle(input.value());
        return true;
    }
    return false;
}


void Manager::insertManager() {

    std::cout << "Is your manager an existing employee? (y/n): ";
    char response;
    std::cin >> response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool newEmpFlag = (response == 'y' || response == 'Y');
    auto _id = newEmpFlag ? getInput<int>("Enter Employee ID: ", "Invalid Input. Please enter Id in Int.", Validation::validateInt) : insertEmployee();

    if (!_id.has_value()) {
        std::cout << "Error inserting Employee. Aborting insertion of Engineer.\n";
        return;
    }

    if (!setExperienceUserInput() || !setProjectTileUserInput()) {
        std::cout << "Error setting Manager data. Aborting insertion.\n";
        if (newEmpFlag) {
            deleteEmployee(_id.value());
        }
        return;
    }

    if (!Database::getInstance().isIdExist(*_id, "employee")) {
        std::cerr << "Employee with ID " << *_id << " does not exist in the database.\n";
        return;
    }

    Database::getInstance().pragmeSwitch(false);
    ManagerController::insertManagerController(*this , *_id);

}

void Manager::deleteManager() {
    if (!setIdFromUserInput()) return;

    if (!ManagerController::deleteManagerController(getId())) {
        std::cout << "Manager Deletion Failed\n";
    }
}
void Manager::updateManager() {
    bool flag = true;
    int choice;
    std::cout << "Enter Manager id to update: \n";
    int _id;
    if (auto idtoUpdate = getInput<int>("Enter Id", "Invalid input. Please enter a non-negative integer.", Validation::validateInt); idtoUpdate.has_value()) {

        _id = idtoUpdate.value();
    }
    else
    {
        return;
    }
    if (!Database::getInstance().isIdExist(_id, "employee")) {
        std::cerr << "Department with ID " << _id << " does not exist in the database.\n";
        return;
    }


    while (flag) {
        std::cout << "Manager Table - Update\n";
        std::cout << "Please select an attribute to update:\n";
        std::cout << "1. Manager's Experience\n";
        std::cout << "2. Project Title\n";
        std::cout << "3. Update Employee Detail\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            if (setExperienceUserInput()) {
                ManagerController::updateManagerController(*this, ManagerAttribute::MANGAEREXPERIENCE ,_id);
                flag = false;
            }
            break;
        case 2:
            if (setProjectTileUserInput()) {
                ManagerController::updateManagerController(*this, ManagerAttribute::PROJECTTITLE,_id);
                flag = false;
            }
            break;
        case 3:
            updateEmployee(_id);
            break;
        case 4:
            flag = false;
            system("cls");
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}



void Manager::viewManager() {
    auto flag{true};
    std::string selectQuery;
    int choice;

    while (flag) {
        selectQuery={};
        std::cout << "Please select a column to view a Manager:\n"
            << "1. ALL\n"
            << "2. Employee Id\n"
            << "3. Exit\n"
            << "Enter your choice (1-3): ";

        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            selectQuery = "SELECT * FROM Employee NATURAL JOIN Manager WHERE Employee.id == Manager.id ";
            ManagerController::viewManagerController(selectQuery);
            break;
        case 2:
            if (setIdFromUserInput()) {
                selectQuery = "SELECT * FROM Employee NATURAL JOIN Manager WHERE Employee.id == Manager.id AND Employee.id = " + std::to_string(getId());
                ManagerController::viewManagerController(selectQuery);
                
            }
            break;
        case 3:
            flag = false;
            return; 
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

}


void Manager::action() {
    system("cls");
    std::map<int, std::pair<std::string, std::function<void()>>> options = {
        {1, {"Insert", std::bind(&Manager::insertManager, this)}},
        {2, {"Delete", std::bind(&Manager::deleteManager, this)}},
        {3, {"Update", std::bind(&Manager::updateManager, this)}},
        {4, {"View", std::bind(&Manager::viewManager, this)}},
        {5, {"Describe",[]() { Database::getInstance().describeTable("Manager"); } }},
        {6, {"Exit", [] {system("cls"); }}}
    };

    executeMenu(options,"Manager Table");
}


