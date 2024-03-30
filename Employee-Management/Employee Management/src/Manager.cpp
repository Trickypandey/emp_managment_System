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

    if (!insertEmployee()) {
        std::cout << "Error Manager Employee. Aborting Manager insertion.\n";
        return;
    }

    if (!setExperienceUserInput()) {
        std::cout << "Error setting Manager experience. Deleting inserted Employee.\n";
        deleteById(Employee::getId());
        return;
    }

    if (!setProjectTileUserInput()) {
        std::cout << "Error setting Manager project title. Deleting inserted Employee.\n";
        deleteById(Employee::getId());
        return;
    }
    

    std::string insertQuery = "INSERT INTO Manager(id, management_experience , project_title) VALUES ("
        + std::to_string(Employee::getId()) + ","
        + std::to_string(management_experience) + ",'"
        + project_title + "');";

    if (Database::getInstance().executeQuery(insertQuery))
        std::cout << "Inserted Manager Successfully! \n\n";
    else
        std::cout << Database::getInstance().getError() << "\n";

}

void Manager::deleteManager() {
    bool executionFlag = false;
    bool flag = true;
    std::string deleteQuery;

    while (flag) {
        deleteQuery.clear();
        std::cout << "Please select a column to delete a manager:\n";
        std::cout << "1. ID\n";
        std::cout << "2. Firstname\n";
        std::cout << "3. Gmail\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            if (setIdFromUserInput()) {
                deleteQuery = "DELETE FROM Manager WHERE id = " + std::to_string(getId());
                executionFlag = true;
            }
            break;
        case 2:
            if (setFirstnameFromUserInput()) {
                deleteQuery = "DELETE FROM Manager WHERE firstname = '" + getFirstname() + "'";
                executionFlag = true;
            }
            break;
        case 3:
            if (setEmailFromUserInput()) {
                deleteQuery = "DELETE FROM Manager WHERE email = '" + getEmail() + "'";
                executionFlag = true;
            }
            break;
        case 4:
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 4.\n";
            break;
        }

        if (executionFlag) {
            if (Database::getInstance().executeQuery(deleteQuery)) {
                int changes = sqlite3_changes(Database::getInstance().db);
                std::cout << changes << " row affected \n\n";
                if (changes != 0) {
                    std::cout << "Manager Deleted Successfully! \n\n";
                }
            }
            else {
                std::cout << Database::getInstance().getError() << "\n";
            }
        }
    }
}
void Manager::updateManager() {
    bool flag = true;
    int choice;
    std::string updateQuery{};
    std::cout << "Enter Manager id to update: \n";
    int _id;
    std::cin >> _id;
    if (!Database::getInstance().isIdExist(_id, "employee")) {
        std::cerr << "Department with ID " << _id << " does not exist in the database.\n";
        return;
    }

    std::cout << "Manager Table - Update\n";
    std::cout << "Please select an attribute to update:\n";
    std::cout << "1. Manager's Experience\n";
    std::cout << "2. Project Title\n";
    std::cout << "2. Update Employee Detail\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice (1-3): ";

    while (flag) {
        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            if (setExperienceUserInput()) {
                updateQuery = generateUpdateQuery("Manager", "management_experience", std::to_string(getManagementExperience()), _id);
                flag = false;
            }
            break;
        case 2:
            if (setProjectTileUserInput()) {
                updateQuery = generateUpdateQuery("Manager", "project_title", getProjectTitle(), _id);
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
            std::cerr << "Invalid choice. Please enter a number between 1 and 3.\n";
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
                std::cout << "Manager Updated Successfully!\n\n";
            }
        }
        else {
            std::cout << "Error updating Manager: " << Database::getInstance().getError() << "\n";
        }
    }
}



void Manager::viewManager() {
    auto flag{true};
    bool executionFlag = false;
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
            executionFlag = true;
            break;
        case 2:
            if (setIdFromUserInput()) {
                selectQuery = "SELECT * FROM Employee NATURAL JOIN Manager WHERE Employee.id == Manager.id AND Employee.id = " + std::to_string(getId());
                executionFlag = true;
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
        if(executionFlag){
            if (!Database::getInstance().executeQueryCallback(selectQuery)) {
                std::cout << Database::getInstance().getError() << std::endl;
            }
        }
    }

}


void Manager::action() {
    std::map<int, std::pair<std::string, std::function<void()>>> options = {
        {1, {"Insert", std::bind(&Manager::insertManager, this)}},
        {2, {"Delete", std::bind(&Manager::deleteManager, this)}},
        {3, {"Update", std::bind(&Manager::updateManager, this)}},
        {4, {"View", std::bind(&Manager::viewManager, this)}},
        {5, {"Describe",[]() { Database::getInstance().describeTable("Department"); } }},
        {6, {"Exit", []() {}}}
    };

    executeMenu(options);
}


