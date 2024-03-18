
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
    if (auto input = getInput<std::string>("Enter Gender (Male, Female, Other): ", "Invalid Input. Please enter your gender.", [](const std::string& s) { return !s.empty(); }); input.has_value()) {
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
    auto input = getInput<int>("Enter Manager ID: ", "Invalid Input. Please enter an integer.", [](int id) { return id >= 0 && Database::getInstance().isIdExist(id, "Employee"); });
    if (input.has_value()) {
        setManagerId(input.value());
        return true;
    }
    return false;
}

bool Employee::setDepartmentIdFromUserInput() {
    auto input = getInput<int>("Enter Department ID: ", "Invalid Format !! Please enter a valid DepartmentId.", [](int id) { return id >= 0 && Database::getInstance().isIdExist(id, "Department"); });
    if (input.has_value()) {
        setDepartmentId(input.value());
        return true;
    }
    return false;
}

void Employee::insertEmployee() { 
    
    std::cout << "Enter Employee Details:\n";

    if (!setUserData()) {
        return;
    }

    std::string insertQuery = "INSERT INTO Employee (id, firstname, lastname, dob, mobile, email, address, gender, doj, w_location, manager_id, department_id) VALUES ("
        + std::to_string(id) + ", '" +
        firstname + "', '" +
        lastname + "', '" +
        dob + "', '" +
        mobile + "', '" +
        email + "', '" +
        address + "', '" +
        gender + "', '" +
        doj + "', '" +
        w_location + "', " +
        std::to_string(manager_id) + ", " +
        std::to_string(department_id) + ");";
 
     if (Database::getInstance().executeQuery(insertQuery))
        std::cout << "Inserted Employee Succesfully ! \n";
    else
         std::cout << Database::getInstance().getError() << "\n";

};

void Employee::deleteEmployee() {
    bool executionFlag = false;
    std::string deleteQuery{};
    bool flag = true;
    int choice;
    while (flag) {
        deleteQuery.clear();
        std::cout << "Please select a column to delete an employee:\n";
        std::cout << "1. ID\n";
        std::cout << "2. Firstname\n";
        std::cout << "3. Gmail\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            if (setIdFromUserInput()) {
                deleteQuery = "DELETE FROM Employee WHERE id = " + std::to_string(getId());
                executionFlag = true;
            }
            break;
        case 2:
            if (setFirstnameFromUserInput()) {
                deleteQuery = "DELETE FROM Employee WHERE firstname = '" + getFirstname() + "'";
                executionFlag = true;
            }
            break;

        case 3:
            if (setEmailFromUserInput()) {
                deleteQuery = "DELETE FROM Employee WHERE email = '" + getEmail() + "'";
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
                    std::cout << "Employee Deleted Successfully ! \n\n";
                }
            }
            else {
                std::cout << Database::getInstance().getError() << "\n";
            }
        }
    }
}


void Employee::updateEmployee() {
    std::string updateQuery{};
    int idToUpdate;
    bool flag = true;
    bool executionFlag = false;

    std::cout << "Enter the ID of the employee you want to update: ";
    std::cin >> idToUpdate;
    if (!Database::getInstance().isIdExist(idToUpdate, "employee")) {
        std::cerr << "Employee with ID " << idToUpdate << " does not exist in the database.\n";
        return;
    }

    while (flag) {
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
                updateQuery = generateUpdateQuery("firstname", getFirstname(), idToUpdate);
                executionFlag = true;
            }
            break;
        case 2:
            if (setLastnameFromUserInput()) {
                updateQuery = generateUpdateQuery("lastname", getLastname(), idToUpdate);
                executionFlag = true;
            }
            break;
        case 3:
            if (setDobFromUserInput()) {
                updateQuery = generateUpdateQuery("dob", getDob(), idToUpdate);
                executionFlag = true;
            }
            break;
        case 4:
            if (setMobileFromUserInput()) {
                updateQuery = generateUpdateQuery("mobile", getMobile(), idToUpdate);
                executionFlag = true;
            }
            break;
        case 5:
            if (setEmailFromUserInput()) {
                updateQuery = generateUpdateQuery("email", getEmail(), idToUpdate);
                executionFlag = true;
            }
            break;
        case 6:
            if (setAddressFromUserInput()) {
                updateQuery = generateUpdateQuery("address", getAddress(), idToUpdate);
                executionFlag = true;
            }
            break;
        case 7:
            if (setGenderFromUserInput()) {
                updateQuery = generateUpdateQuery("gender", getGender(), idToUpdate);
                executionFlag = true;
            }
            break;
        case 8:
            if (setDojFromUserInput()) {
                updateQuery = generateUpdateQuery("doj", getDoj(), idToUpdate);
                executionFlag = true;
            }
            break;
        case 9:
            if (setWLocationFromUserInput()) {
                updateQuery = generateUpdateQuery("w_location", getWLocation(), idToUpdate);
                executionFlag = true;
            }
            break;
        case 10:
            if (setManagerIdFromUserInput()) {
                updateQuery = generateUpdateQuery("manager_id", std::to_string(getManagerId()), idToUpdate);
                executionFlag = true;
            }
            break;
        case 11:
            if (setDepartmentIdFromUserInput()) {
                updateQuery = generateUpdateQuery("department_id", std::to_string(getDepartmentId()), idToUpdate);
                executionFlag = true;
            }
            break;
        case 12:
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 12.\n";
            break;
        }

    }
    if (executionFlag && !updateQuery.empty()) { 
        if (Database::getInstance().executeQuery(updateQuery))
            std::cout << "Employee information updated successfully!\n";
        else
            std::cout << "Failed to update employee information: " << Database::getInstance().getError() << "\n";
    }
}


std::string Employee::generateUpdateQuery(const std::string& fieldName, const std::string& value, int idToUpdate) {
    return "UPDATE Employee SET " + fieldName + " = '" + value + "' WHERE id = " + std::to_string(idToUpdate);
}

void Employee::viewEmployee() { 


    std::string selectQuery{};
    bool flag = true;
    int choice;
    while (flag) {

        std::cout << "Please select a column to view an employee:\n";
        std::cout << "1. ALL\n";
        std::cout << "2. ID\n";
        std::cout << "3. Firstname\n";
        std::cout << "4. Gmail\n";
        std::cout << "5. Exit\n";

        std::cout << "Enter your choice (1-5): ";


        std::cin >> choice;


        switch (choice) {
        case 1:
            selectQuery = "SELECT * FROM Employee";

            if (!Database::getInstance().executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << Database::getInstance().getError() << std::endl;
            }
            break;
        case 2:
            setIdFromUserInput();
            selectQuery = "SELECT * FROM Employee WHERE id = " + std::to_string(getId());
            if (!Database::getInstance().executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << Database::getInstance().getError() << std::endl;
            }
            break;
        case 3:
            setFirstnameFromUserInput();
            selectQuery = "SELECT * FROM Employee WHERE firstname = '" + getFirstname() + "'";
            if (!Database::getInstance().executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << Database::getInstance().getError() << std::endl;
            }
            break;

        case 4:
            setEmailFromUserInput();
            selectQuery = "SELECT * FROM Employee WHERE email = '" + getEmail() + "'";
            if (!Database::getInstance().executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << Database::getInstance().getError() << std::endl;
            }
            break;

        case 5:
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
            break;
        }
    }
};

void Employee::action() {
    bool flag = true;

    int choice;


    while (flag) {

        std::cout << "Employee Table\n";
        std::cout << "Please select a value to perform actions:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Delete\n";
        std::cout << "3. Update\n";
        std::cout << "4. View\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1-5): ";

        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            insertEmployee();
            break;
        case 2:
            deleteEmployee();
            break;
        case 3:
            updateEmployee();
            break;
        case 4:
            viewEmployee();
            break;
        case 5:
            flag = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            break;
        }
    }
}
