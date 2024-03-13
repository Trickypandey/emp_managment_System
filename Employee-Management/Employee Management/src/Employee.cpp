
#include "../include/Employee.h"
#include "../include/validate.h"

bool Employee::setIdFromUserInput() {
    std::cout << "Enter Employee ID: ";
    std::cin >> id;
    setId(id);
    return true;
}

bool Employee::setFirstnameFromUserInput() {
    std::cout << "Enter First Name: ";
    std::cin >> firstname;
    setFirstname(firstname);
    return true;
}

bool Employee::setLastnameFromUserInput() {
    std::cout << "Enter Last Name: ";
    std::cin >> lastname;
    setLastname(lastname);
    return true;
}

bool Employee::setDobFromUserInput() {      
    bool validInput = false;
    int count = 0; 
    do {
        if (count > 3) {
            std::cout << "Maximum number of attempts reached.\n";
            return false; 
        }
        std::cout << "Enter Date of Birth (DD-MM-YYYY): ";
        std::cin >> dob;
        if (!validateDateOfBirth(dob)) {
            std::cout << "Invalid date format. Please enter the date in DD-MM-YYYY format.\n";
            count++; 
        }
        else {
            validInput = true;
            setDob(dob);
        }
    } while (!validInput);

    return true;
}

bool Employee::setMobileFromUserInput() {
    bool validInput = false;
    int count = 0;
    do {
        if (count > 3) {
            std::cout << "Maximum number of attempts reached.\n";
            return false;
        }
        std::cout << "Enter Mobile number : ";
        std::cin >> mobile;
        if (!validatePhoneNumber(mobile)) {
            std::cout << "Invalid Format !! Please enter a valid mobile number.\n";
            count++;
        }
        else
        {
            validInput = true;
            setMobile(mobile);
        }
    } while (!validInput);
    return true;
}

bool Employee::setEmailFromUserInput() {
    bool validInput = false;
    int count = 0;
    do {
        if (count > 3) {
            std::cout << "Maximum number of attempts reached.\n";
            return false;
        }
        std::cout << "Enter Email address : ";
        std::cin >> email;
        if (!validateEmail(email)) {
            std::cout << "Invalid Format !! Please enter a valid email address.\n";
            count++;
        }
        else
        {
            validInput = true;
            setEmail(email);
        }
    } while (!validInput);
    return true;
}

bool Employee::setAddressFromUserInput() {
    std::cout << "Enter Address: ";
    std::cin.ignore();
    std::getline(std::cin, address);
    setAddress(address);
    return true;
}

bool Employee::setGenderFromUserInput() {
    std::cout << "Enter Gender (Male, Female, Other): ";
    std::cin >> gender;
    setGender(gender);
    return true;
}

bool Employee::setDojFromUserInput() {
    bool validInput = false;
    int count = 0;
    do {
        if (count > 3) {
            std::cout << "Maximum number of attempts reached.\n";
            return false;
        }
        std::cout << "Enter Date of Joining (DD-MM-YYYY): ";
        std::cin >> doj;
        if (!validateDateOfBirth(doj)) {
            std::cout << "Invalid date format. Please enter the date in DD-MM-YYYY format.\n";
            count++;
        }
        else {
            validInput = true;
            setDoj(doj);
        }
    } while (!validInput);
    return true;
}

bool Employee::setWLocationFromUserInput() {
    std::cout << "Enter Work Location: ";
    std::cin >> w_location;
    setWLocation(w_location);
    return true;
}

bool Employee::setManagerIdFromUserInput() {
    std::cout << "Enter Manager ID: ";
    std::cin >> manager_id;
    setManagerId(manager_id);
    return true;
}

bool  Employee::setDepartmentIdFromUserInput() {
    bool validInput = false;
    int count = 0;

    do {
        if (count > 3) {
            std::cout << "Maximum number of attempts reached.\n";
            return false;
        }
        std::cout << "Enter Department ID: ";
        std::cin >> department_id;
        if (!Database::getInstance().isIdExist(department_id, "Department")) {
            std::cout << "Invalid Format !! Please enter a valid DepartmentId.\n";
            count++;
        }
        else
        {
            validInput = true;
            setDepartmentId(department_id);
           
        }
    } while (!validInput);
    return true;
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
    std::string deleteQuery{};
    bool flag = true;
    int choice;
    while (flag) {

        std::cout << "Please select a column to delete an employee:\n";
        std::cout << "1. ID\n";
        std::cout << "2. Firstname\n";
        std::cout << "3. Gmail\n";
        std::cout << "4. Exit\n";

        std::cout << "Enter your choice (1-4): ";


        std::cin >> choice;


        switch (choice) {
        case 1:
            setIdFromUserInput();
            deleteQuery = "DELETE FROM Employee WHERE id = " + std::to_string(getId());
            
            break;
        case 2:
            setFirstnameFromUserInput();
            deleteQuery = "DELETE FROM Employee WHERE firstname = '" + getFirstname()+ "'";
            
            break;

        case 3:
            setEmailFromUserInput();
            deleteQuery = "DELETE FROM Employee WHERE email = '" + getEmail() + "'";
            
            break;

        case 4:
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 4.\n";
            break;
        }
        if (Database::getInstance().executeQuery(deleteQuery)) {

            int changes = sqlite3_changes(Database::getInstance().db);

            std::cout << changes << " row affected \n\n";
            if (changes != 0) {
                std::cout << "Employee Deleted Succesfully ! \n\n";
            }

        }
        else
            std::cout << Database::getInstance().getError() << "\n";
    }
};

void Employee::updateEmployee() {
    std::string updateQuery{};
    int idToUpdate;
    bool flag = true;

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
            setFirstnameFromUserInput();
            updateQuery = generateUpdateQuery("firstname", getFirstname(), idToUpdate);
            break;
        case 2:
            setLastnameFromUserInput();
            updateQuery = generateUpdateQuery("lastname", getLastname(), idToUpdate);
            break;
        case 3:
            setDobFromUserInput();
            updateQuery = generateUpdateQuery("dob", getDob(), idToUpdate);
            break;
        case 4:
            setMobileFromUserInput();
            updateQuery = generateUpdateQuery("mobile", getMobile(), idToUpdate);
            break;
        case 5:
            setEmailFromUserInput();
            updateQuery = generateUpdateQuery("email", getEmail(), idToUpdate);
            break;
        case 6:
            setAddressFromUserInput();
            updateQuery = generateUpdateQuery("address", getAddress(), idToUpdate);
            break;
        case 7:
            setGenderFromUserInput();
            updateQuery = generateUpdateQuery("gender", getGender(), idToUpdate);
            break;
        case 8:
            setDojFromUserInput();
            updateQuery = generateUpdateQuery("doj", getDoj(), idToUpdate);
            break;
        case 9:
            setWLocationFromUserInput();
            updateQuery = generateUpdateQuery("w_location", getWLocation(), idToUpdate);
            break;
        case 10:
            setManagerIdFromUserInput();
            updateQuery = generateUpdateQuery("manager_id", std::to_string(getManagerId()), idToUpdate);
            break;
        case 11:
            setDepartmentIdFromUserInput();
            updateQuery = generateUpdateQuery("department_id", std::to_string(getDepartmentId()), idToUpdate);
            break;
        case 12:
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 12.\n";
            continue;
        }

        if (flag) {
            if (Database::getInstance().executeQuery(updateQuery))
                std::cout << "Employee information updated successfully!\n";
            else
                std::cout << "Failed to update employee information: " << Database::getInstance().getError() << "\n";
        }
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
