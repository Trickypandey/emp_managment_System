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
    if (auto input = getInput<int>("Enter manager ID(-1 for Empty): ", "Invalid Input. Please enter an integer.", [](int id) { return id >= 0 && Database::getInstance().isIdExist(id, "Employee"); }); input.has_value()) {
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

    std::string insertQuery = "INSERT INTO Department (id, name, manager_id, description) VALUES ("
        + std::to_string(id) + ", '" +
        name + "', " +
        (getManagerId() == -1 ? "null" : std::to_string(getManagerId())) + + ", '" +
        description + "');";

    if (Database::getInstance().executeQuery(insertQuery)) {
        std::cout << "Inserted Department Successfully!\n";
    }
    else {
        std::cout << Database::getInstance().getError() << "\n";
    }
}

void Department::deleteDepartment() {
    std::string deleteQuery{};

    int choice;
    bool flag = true;
    system("cls");
    while (flag) {
        bool executionFlag = false; 
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
                deleteQuery = "DELETE FROM Department WHERE id = " + std::to_string(getId());
                executionFlag = true; 
            }
            break;
        case 2:
            if (setDNameFromUserInput()) { 
                deleteQuery = "DELETE FROM Department WHERE name = '" + getName() + "'";
                executionFlag = true; 
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
        if (executionFlag && Database::getInstance().executeQuery(deleteQuery)) {
            int changes = sqlite3_changes(Database::getInstance().db);
            std::cout << changes << " row affected \n\n";
            if (changes != 0) {
                std::cout << "Department Deleted Successfully ! \n";
            }
        }
        else {
            std::cout << Database::getInstance().getError() << "\n";
        }
    }

}

void Department::updateDepartment() {
    std::string updateQuery{};
   
    system("cls");
    int choice;
    int _id;
    bool flag = true;

    std::cout << "Enter Department id to update: \n";
    std::cin >> _id;
    if (!Database::getInstance().isIdExist(_id, "Department")) {
        std::cerr << "Department with ID " << _id << " does not exist in the database.\n";
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
                updateQuery = generateUpdateQuery("Department", "name", getName(), _id);
                executionFlag = true;
            }
            break;
        case 2:
            if (setDManagerIdFromUserInput()) {
                updateQuery = generateUpdateQuery("Department", "manager_id", std::to_string(getManagerId()), _id);
                executionFlag = true;
            }
            break;
        case 3:
            if (setDescriptionFromUserInput()) {
                updateQuery = generateUpdateQuery("Department", "description", getDescription(), _id);
                executionFlag = true;
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
        if (executionFlag && !updateQuery.empty()) {
            if (Database::getInstance().executeQuery(updateQuery)) {
                int changes = sqlite3_changes(Database::getInstance().db);
                std::cout << changes << " row affected \n\n";
                if (changes != 0) {
                    std::cout << "Department Updated Successfully! \n";
                }
            }
            else {
                std::cout << "Error executing update query: " << Database::getInstance().getError() << "\n";
            }
        }
        else {
            std::cout << "No attribute selected for update.\n";
        }
    }

}

void Department::viewDepartment() {
    std::string selectQuery{};

    int choice;
    bool flag = true;
    system("cls");

    while (flag) {
        bool executionFlag = false; 
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
            selectQuery = "SELECT * FROM Department";
            executionFlag = true; 
            break;
        case 2:
            if (setDidFromUserInput()) { 
                selectQuery = "SELECT * FROM Department WHERE id = " + std::to_string(getId());
                executionFlag = true; 
            }
            break;
        case 3:
            if (setDNameFromUserInput()) { 
                selectQuery = "SELECT * FROM Department WHERE name = '" + getName() + "'";
                executionFlag = true;
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
        if (executionFlag && !Database::getInstance().executeQueryCallback(selectQuery)) {
            std::cout << Database::getInstance().getError() << std::endl;
        }
    }

}

void Department::action() {
    std::map<int, std::pair<std::string, std::function<void()>>> options = {
        {1, {"Insert", std::bind(&Department::insertDepartment, this)}},
        {2, {"Delete", std::bind(&Department::deleteDepartment, this)}},
        {3, {"Update", std::bind(&Department::updateDepartment, this)}},
        {4, {"View", std::bind(&Department::viewDepartment, this)}},
        {5, {"Describe", []() { Database::getInstance().describeTable("Department"); }}},
        {6, {"Exit", []() {}}}
    };

    executeMenu(options);
}

