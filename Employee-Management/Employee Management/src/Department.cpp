#include "../include/Department.h"

void Department::setIdFromUserInput() {
    std::cout << "Enter department ID: ";
    std::cin >> id;
    setId(id);
}

void Department::setNameFromUserInput() {
    std::cout << "Enter department name: ";
    std::cin.ignore(); 
    std::getline(std::cin, name);
    setName(name);
}

void Department::setManagerIdFromUserInput() {
    std::cout << "Enter manager ID: ";
    std::cin >> manager_id;
    setManagerId(manager_id);
}

void Department::setDescriptionFromUserInput() {
    std::cout << "Enter department description: ";
    std::cin.ignore(); 
    std::getline(std::cin, description);
    setDescription(description);
}

void Department::insertDepartment() {

    std::cout << "Enter Department Details:\n";
    setIdFromUserInput();
    setNameFromUserInput();
    setManagerIdFromUserInput();
    setDescriptionFromUserInput();

    std::string insertQuery = "INSERT INTO Department (id, name, manager_id, description) VALUES ("
        + std::to_string(id) + ", '" +
        name + "', " +
        std::to_string(manager_id) + ", '" +
        description + "');";

    if (db_department.executeQuery(insertQuery))
        std::cout << "Inserted Department Successfully!\n";
    else
        std::cout << db_department.getError() << "\n";

};
void Department::deleteDepartment() {};
void Department::updateDepartment() {};
void Department::viewDepartment() {};
 


void Department::action() {
    bool flag = true;


    int choice;

    while (flag) {
        std::cout << "Department Table\n";
        std::cout << "Please select a value to perform actions:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Delete\n";
        std::cout << "3. Update\n";
        std::cout << "4. View\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            insertDepartment();
            break;
        case 2:
            deleteDepartment();
            break;
        case 3:
            updateDepartment();
            break;
        case 4:
            viewDepartment();
            break;
        case 5: 
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
            break;
        }
    }
}
