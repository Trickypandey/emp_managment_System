#include "../include/Engineer.h"
using namespace Utility;
bool Engineer::setProgLangUserInput() {
    
    if (auto input = getInput<std::string>("Enter Programming Language (separated by comma if multiple): ", "Invalid input. Please try again.", [](const std::string& str) { return !str.empty() && Validation::validateString(str); }); input.has_value()) {
        setProgrammingLanguage(input.value());
        return true;
    }
    else {
        return false;
    }
}

bool Engineer::setSpecializationUserInput() {
    
    if (auto input = getInput<std::string>("Enter Specialization: ", "Invalid input. Please try again.", [](const std::string& str) { return !str.empty() && Validation::validateString(str); }); input.has_value()) {
        setSpecialization(input.value());
        return true;
    }
    else {
        return false;
    }
}



void Engineer::insertEngineer() {
    std::cout << "Is your engineer an existing employee? (y/n): ";
    char response;
    std::cin >> response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool newEmpFlag = (response == 'y' || response == 'Y');
    std::optional<int> _id = newEmpFlag ? getInput<int>("Enter Employee ID: ", "Invalid Input. Please enter Id in Int.", Validation::validateInt) : insertEmployee();

    if (!_id.has_value()) {
        std::cout << "Error inserting Employee. Aborting insertion of Engineer.\n";
        return;
    }

    if (!setProgLangUserInput() || !setSpecializationUserInput()) {
        std::cout << "Error setting Engineer data. Aborting insertion.\n";
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
    EngineerController::insertEngineerController(*this , *_id);
}

void Engineer::deleteEngineer() {
    if (!setIdFromUserInput()) return;

    if (!EngineerController::deleteEngineerController(getId())) {
        std::cout << "engineer Deletion Failed\n";
    }
}

void Engineer::updateEngineer() {
    bool flag = true;
    
    std::string updateQuery{};
    int choice;

    std::cout << "Enter Employee id to update: \n";
    int _id;
    std::cin >> _id;
    if (!Database::getInstance().isIdExist(_id, "employee")) {
        std::cerr << "Employee with ID " << _id << " does not exist in the database.\n";
        return;
    }

    while (flag) {
        std::cout << "Please select an attribute to update:\n";
        std::cout << "1. Programming Language\n";
        std::cout << "2. Specialization\n";
        std::cout << "3. Update Employee Details\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-3): ";

        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            if (setProgLangUserInput()) {
                updateQuery = generateUpdateQuery("Engineer", "programming_language", getProgrammingLanguage(),_id);
                flag = false;
            }
            break;
        case 2:
            if (setSpecializationUserInput()) {
                updateQuery = generateUpdateQuery("Engineer", "specialization", getSpecialization(), _id);
                flag = false;
            }
            break;
        case 3:
            updateEmployee(_id);
            break;
        case 4:
            flag = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    if (!updateQuery.empty()) {
        if (Database::getInstance().executeQuery(updateQuery)) {
            int changes = sqlite3_changes(Database::getInstance().db);
            std::cout << changes << " row affected \n\n";
            if (changes != 0) {
                std::cout << "Engineer Updated Successfully!\n\n";
            }
        }
        else {
            std::cout << "Error updating engineer: " << Database::getInstance().getError() << "\n";
        }
    }
}

void Engineer::viewEngineer() {
    bool flag = true;
    std::string selectQuery{};
    int choice;

    while (flag) {
        std::cout << "Please select a column to view an Engineer:\n";
        std::cout << "1. ALL\n";
        std::cout << "2. Employee Id\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";

        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            selectQuery = "SELECT * FROM Employee NATURAL JOIN Engineer WHERE Employee.id == Engineer.id ";
            flag = false;
            break;
        case 2:
            if (setIdFromUserInput())
            {
                selectQuery = "SELECT * FROM Employee NATURAL JOIN Engineer WHERE Employee.id == Engineer.id AND Employee.id = " + std::to_string(getId());
                flag = false;
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

    if (!Database::getInstance().executeQueryCallback(selectQuery)) {
        std::cout << Database::getInstance().getError() << std::endl;
    }
}



void Engineer::action() {
    std::cout << "Engineer" << std::endl;
    std::map<int, std::pair<std::string, std::function<void()>>> options = {
        {1, {"Insert", std::bind(&Engineer::insertEngineer, this)}},
        {2, {"Delete", std::bind(&Engineer::deleteEngineer, this)}},
        {3, {"Update", std::bind(&Engineer::updateEngineer, this)}},
        {4, {"View", std::bind(&Engineer::viewEngineer, this)}},
        {5, {"Describe",[] {Database::getInstance().describeTable("Engineer"); }}},
        {6, {"Exit", []{system("cls"); }}}
    };

    executeMenu(options);
}

