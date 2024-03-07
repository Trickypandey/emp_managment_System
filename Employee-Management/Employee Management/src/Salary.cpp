#include "../include/Salary.h"

void Salary::insertSalary() { 
    
    /*if (db_salary.executeQuery(insertQuery))
        std::cout << "Inserted Employee Succesfully ! \n";
    else
        std::cout << db_salary.getError() << "\n";*/
};
void Salary::deleteSalary() {return;};
void Salary::updateSalary() {return;};
void Salary::viewSalary() {return;};


void Salary::action() {
    bool flag = true;

    std::cout << "Salary Table\n";
    std::cout << "Please select a value to perform actions:\n";
    std::cout << "1. Insert\n";
    std::cout << "2. Delete\n";
    std::cout << "3. Update\n";
    std::cout << "4. View\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice (1-5): ";

    int choice;
    std::cin >> choice;

    while (flag) {
        switch (choice) {
        case 1:
            insertSalary();
            break;
        case 2:
            deleteSalary();
            break;
        case 3:
            updateSalary();
            break;
        case 4:
            viewSalary();
            break;
        case 5: // Exit
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
            break;
        }
    }
}
