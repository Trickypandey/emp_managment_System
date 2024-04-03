
#include "../include/Employee.h"
#include "../include/validate.h"
using namespace Utility;
bool Employee::setIdFromUserInput() {
    if (auto input = getInput<int>("Enter Employee ID: ", "Invalid Input. Please enter Id in Int.", Validation::validateInt); input.has_value()) {
        setId(input.value());
        return true;
    }
    return false;
}

bool Employee::setFirstnameFromUserInput() {
    if (auto input = getInput<std::string>("Enter First Name: ", "Invalid Input. Please enter a non-empty string.", Validation::validateString); input.has_value()) {
        setFirstname(input.value());
        return true;
    }
    return false;
}

bool Employee::setLastnameFromUserInput() { 
    if (auto input = getInput<std::string>("Enter Last Name: ", "Invalid Input. Please enter a non-empty string.", Validation::validateString); input.has_value()) {
        setLastname(input.value());
        return true;
    }
    return false;
}

bool Employee::setDobFromUserInput() {
    if (auto input = getInput<std::string>("Enter Date of Birth (DD-MM-YYYY): ", "Invalid date format. Please enter the date in DD-MM-YYYY format.", Validation::validateDateOfBirth); input.has_value()) {
        setDob(input.value());
        return true;
    }
    return false;
}

bool Employee::setMobileFromUserInput() {
    if (auto input = getInput<std::string>("Enter Mobile number: ", "Invalid Format !! Please enter a valid mobile number.", Validation::validatePhoneNumber); input.has_value()) {
        setMobile(input.value());
        return true;
    }
    return false;
}

bool Employee::setEmailFromUserInput() {
    if (auto input = getInput<std::string>("Enter Email address: ", "Invalid Format !! Please enter a valid email address.", Validation::validateEmail); input.has_value()) {
        setEmail(input.value());
        return true;
    }
    return false;
}

bool Employee::setAddressFromUserInput() {
    if (auto input = getInput<std::string>("Enter Address: ", "Invalid Input. Please enter an address.", [](const std::string& s) { return !s.empty(); }); input.has_value()) {
        setAddress(input.value());
        return true;
    }
    return false;
}

bool Employee::setGenderFromUserInput() {
    if (auto input = getInput<std::string>("Enter Gender (Male, Female, Other): ", "Invalid Input. Please enter your gender.", [](const std::string& s) { return !s.empty() && ( s == "Male" || s == "Female" || s == "Other"); }); input.has_value()) {
        setGender(input.value());
        return true;
    }
    return false;
}

bool Employee::setDojFromUserInput() {
    if (auto input = getInput<std::string>("Enter Date of Joining (DD-MM-YYYY): ", "Invalid date format. Please enter the date in DD-MM-YYYY format.", Validation::validateDateOfBirth); input.has_value()) {
        setDoj(input.value());
        return true;
    }
    return false;
}

bool Employee::setWLocationFromUserInput() {
    if (auto input = getInput<std::string>("Enter Work Location: ", "Invalid Input. Please enter a non-empty string.", [](const std::string& s) { return !s.empty(); }); input.has_value()) {
        setWLocation(input.value());
        return true;
    }
    return false;
}

bool Employee::setManagerIdFromUserInput() {
    auto input = getInput<int>("Enter Manager ID(-1 for null): ", "Invalid Input. Please enter an integer.", [](int id) {  if (id == -1) { return true; }return id >= 0 && Database::getInstance().isIdExist(id, "Employee"); });
    if (input.has_value()) {
        if (input.value() == -1)
        {

            setManagerId(NULL);
            return true;
        }
        setManagerId(input.value());
        return true;
    }
    return false;
}

bool Employee::setDepartmentIdFromUserInput() {
    auto input = getInput<int>("Enter Department ID(-1 for null): ", "Invalid Format !! Please enter a valid DepartmentId.", [](int id) {if (id == -1) { return true; } return id >= 0 && Database::getInstance().isIdExist(id, "Department"); });
    if (input.has_value()) {
        if (input.value() == -1)
        {

            setDepartmentId(NULL);
            return true;
        }
        setDepartmentId(input.value());
        return true;
    }
    return false;
}

std::optional<int> Employee::insertEmployee() { 
    
    std::cout << "Enter Employee Details:\n";

    if (!setUserData()) {
        return std::nullopt;
    }

    EmployeeController::insertEmployee(*this);
};

bool Employee::deleteEmployee(std::optional<int> deleteId) {
    int _id;

    if (deleteId.has_value()) {
        _id = deleteId.value();
    }
    else {
        auto inputId = getInput<int>("Enter ID: ", "Invalid input. Please enter ID as an integer.", Validation::validateInt);
        if (!inputId.has_value()) {
            std::cout << "Deletion aborted.\n";
            return false;
        }
        _id = inputId.value();
    }

    return EmployeeController::deleteEmployee(_id);
}

void Employee::updateEmployee(std::optional<int> id) {
    std::string updateQuery{};
    int idToUpdate;
    bool flag = true;

    if(!id.has_value()){
        std::cout << "Enter the ID of the employee you want to update: ";
        std::cin >> idToUpdate;
    }
    else
    {
        idToUpdate = id.value();
    }
    if (!Database::getInstance().isIdExist(idToUpdate, "employee")) {
        std::cerr << "Employee with ID " << idToUpdate << " does not exist in the database.\n";
        return;
    }

    this->setId(idToUpdate);
    while (flag) {
        bool executionFlag = false;
        std::cout << "Select the field to update:\n";
        std::cout << "1. First Name\n";
        std::cout << "2. Last Name\n";
        std::cout << "3. Date of Birth\n";
        std::cout << "4. Mobile Number\n";
        std::cout << "5. Email Address\n";
        std::cout << "6. Address\n";
        std::cout << "7. Gender\n";
        std::cout << "8. Date of Joining\n";
        std::cout << "9. Work Location\n";
        std::cout << "10. Manager ID\n";
        std::cout << "11. Department ID\n";
        std::cout << "12. Exit\n";
        std::cout << "Enter your choice (1-12): ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            if (setFirstnameFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::FIRST_NAME);
            }
            break;
        case 2:
            if (setLastnameFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::LAST_NAME);
            }
            break;
        case 3:
            if (setDobFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::DATE_OF_BIRTH);
            }
            break;
        case 4:
            if (setMobileFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::MOBILE_NUMBER);
            }
            break;
        case 5:
            if (setEmailFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::EMAIL_ADDRESS);
            }
            break;
        case 6:
            if (setAddressFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::ADDRESS);
            }
            break;
        case 7:
            if (setGenderFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::GENDER);
            }
            break;
        case 8:
            if (setDojFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::DATE_OF_JOINING);
            }
            break;
        case 9:
            if (setWLocationFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::WORK_LOCATION);
            }
            break;
        case 10:
            if (setManagerIdFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::MANAGER_ID);
            }
            break;
        case 11:
            if (setDepartmentIdFromUserInput()) {
                executionFlag = EmployeeController::updateEmployee(*this, EmployeeAttribute::DEPARTMENT_ID);
            }
            break;

        case 12:
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 12.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

void Employee::viewEmployee() { 
    std::string selectQuery{};

    int choice;
    bool flag = true;
    system("cls");

    while (flag) {
        std::cout << "Please select a column to view an employee:\n";
        std::cout << "1. ALL\n";
        std::cout << "2. ID\n";
        std::cout << "3. Firstname\n";
        std::cout << "4. Email\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            EmployeeController::viewEmployee(*this ,EmployeeViewAttribute::ALL);
            
            break;
        case 2:
            if (setIdFromUserInput())
            {
                EmployeeController::viewEmployee(*this ,EmployeeViewAttribute::ID);
            }
            
            break;
        case 3:
            if (setFirstnameFromUserInput())
            {
                EmployeeController::viewEmployee(*this ,EmployeeViewAttribute::FIRSTNAME);
            }
           
            break;
        case 4:
            if (setEmailFromUserInput())
            {
                EmployeeController::viewEmployee(*this ,EmployeeViewAttribute::EMAIL);
            }
           
            break;
        case 5:
            flag = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
};

void Employee::action() {
    std::cout << "Employee" << std::endl;
    std::map<int, std::pair<std::string, std::function<void()>>> options = {
        {1, {"Insert", std::bind(&Employee::insertEmployee, this)}},
        {2, {"Delete", std::bind(&Employee::deleteEmployee, this,std::nullopt)}},
        {3, {"Update", std::bind(&Employee::updateEmployee, this,std::nullopt)}},
        {4, {"View", std::bind(&Employee::viewEmployee, this)}},
        {5, {"Describe", []() { Database::getInstance().describeTable("Employee"); }}},
        {6, {"Exit", [] {system("cls"); }}}
    };
    executeMenu(options);
}