#include "../include/Department.h"
using namespace Utility;
bool Department::setDidFromUserInput() {
    if (auto input = getInput<int>("Enter department ID: ", "Invalid Input. Please enter Id in Int.", Validation::validateInt); input.has_value()) {
        setId(input.value());
        return true;
    }
    return false;
}

bool Department::setDNameFromUserInput() {
    if (auto input = getInput<std::string>("Enter department name: ", "Invalid Input. Please enter a non-empty string.", [](const std::string& s) { return !s.empty(); }); input.has_value()) {
        setName(input.value());
        return true;
    }
    return false;
}

bool Department::setDManagerIdFromUserInput() {
    if (auto input = getInput<int>("Enter manager ID(-1 for Empty): ", "Invalid Input. Please enter an integer.",
        [](int id) { 
            if (Validation::validateNumeric(id) && id == -1) {
                return true;
            }
            return id >= 0 && Database::getInstance().isIdExist(id, "Employee");
            }
    ); input.has_value()) {
        setManagerId(input.value());
        return true;
    }
    return false;
}

bool Department::setDescriptionFromUserInput() {
    if (auto input = getInput<std::string>("Enter department description: ", "Invalid Input. Please enter a non-empty string.", [](const std::string& s) { return !s.empty() && Validation::validateString(s); }); input.has_value()) {
        setDescription(input.value());
        return true;
    }
    return false;
}

void Department::insertDepartment() {
    system("cls");
    std::cout << "Enter Department Details:\n";
    if (!setDepartemntData()) {
        return;
    }
    
    DepartmentController::insertDepartmentController(*this);
}

void Department::deleteDepartment() {
    int choice;
    bool flag = true;
    system("cls");
    while (flag) {
        std::cout << "Please select a column to delete a Department:\n";
        std::cout << "1. ID\n";
        std::cout << "2. Dept. Name\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            if (setDidFromUserInput()) { 
                DepartmentController::deleteDepartmentController(*this, DepartmentAttribute::ID);
            }
            break;
        case 2:
            if (setDNameFromUserInput()) { 
                DepartmentController::deleteDepartmentController(*this, DepartmentAttribute::NAME);
            }
            break;
        case 3:
            flag = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

void Department::updateDepartment() {
  
    system("cls");
    int choice;
    bool flag = true;

    if (auto idToUpdate = getInput<int>("enter the Id to Update", "Invalid Input. Please enter Id in Int", Validation::validateInt); !idToUpdate.has_value()) {
        std::cout << "Aborting Updation \n";
    }
    else
    {
        setId(idToUpdate.value());
    }

    if (!Database::getInstance().isIdExist(getId(),"Department")) {
        std::cerr << "Department with ID " << getId() << " does not exist in the database.\n";
        return;
    }

    while (flag) {
        bool executionFlag = false;
        std::cout << "Please select an attribute to update:\n";
        std::cout << "1. Dept. Name\n";
        std::cout << "2. Dept. Manager_Id\n";
        std::cout << "3. Description\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            if (setDNameFromUserInput()) {
                executionFlag = DepartmentController::updateDepartmentController(*this, DepartmentAttribute::NAME);
            }
            break;
        case 2:
            if (setDManagerIdFromUserInput()) {
                executionFlag = DepartmentController::updateDepartmentController(*this, DepartmentAttribute::MANAGER_ID);
            }
            break;
        case 3:
            if (setDescriptionFromUserInput()) {
                executionFlag = DepartmentController::updateDepartmentController(*this, DepartmentAttribute::DESCRIPTION);
            }
            break;
        case 4:
            flag = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

}

void Department::viewDepartment() {
    
    int choice;
    bool flag = true;
    system("cls");

    while (flag) {
        std::cout << "Please select a column to view a Department:\n";
        std::cout << "1. ALL\n";
        std::cout << "2. Dept.Id\n";
        std::cout << "3. Dept. Name\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            DepartmentController::viewDepartmentController(*this ,DepartmentViewAttribute::ALL);
            break;
        case 2:
            if (setDidFromUserInput()) { 
                DepartmentController::viewDepartmentController(*this, DepartmentViewAttribute::ID);
               
            }
            break;
        case 3:
            if (setDNameFromUserInput()) { 
                DepartmentController::viewDepartmentController(*this, DepartmentViewAttribute::NAME);
            }
            break;
        case 4:
            flag = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

}

void Department::action() {
    std::cout << "Department" << std::endl;
    std::map<int, std::pair<std::string, std::function<void()>>> options = {
        {1, {"Insert", std::bind(&Department::insertDepartment, this)}},
        {2, {"Delete", std::bind(&Department::deleteDepartment, this)}},
        {3, {"Update", std::bind(&Department::updateDepartment, this)}},
        {4, {"View", std::bind(&Department::viewDepartment, this)}},
        {5, {"Describe", []() { Database::getInstance().describeTable("Department"); }}},
        {6, {"Exit", [] {system("cls"); }}}
    };

    executeMenu(options);
}

