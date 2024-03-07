
#include "../include/Employee.h"
#include "../include/validate.h"

void Employee::setIdFromUserInput() {
    std::cout << "Enter Employee ID: ";
    std::cin >> id;
    setId(id);
}

void Employee::setFirstnameFromUserInput() {
    std::cout << "Enter First Name: ";
    std::cin >> firstname;
    setFirstname(firstname);
}

void Employee::setLastnameFromUserInput() {
    std::cout << "Enter Last Name: ";
    std::cin >> lastname;
    setLastname(lastname);
}

void Employee::setDobFromUserInput() {      
    bool validInput = false;
    auto count = 0;
    do {
        if (count > 3)
        {
            std::cout << "maximum number of attemps reach \n";

        }
        std::cout << "Enter Date of Birth (DD-MM-YYYY): ";
        std::cin >> dob; 
        if (!validateDateOfBirth(dob)) {
            std::cout << "Invalid date format. Please enter the date in DD-MM-YYYY format.\n";
        }
        else {
            validInput = true;
            setDob(dob);
        }
    } while (!validInput);
}

void Employee::setMobileFromUserInput() {
    do {
        std::cout << "Enter Mobile number : ";
        std::cin >> mobile;
        if (!validatePhoneNumber(mobile)) {
            std::cout << "Invalid Format !! Please enter a valid mobile number.\n";
        }
        else
        {
            setMobile(mobile);
        }
    } while (!validatePhoneNumber(mobile));
}

void Employee::setEmailFromUserInput() {
    do {
        std::cout << "Enter Email address : ";
        std::cin >> email;
        if (!validateEmail(email)) {
            std::cout << "Invalid Format !! Please enter a valid email address.\n";
        }
        else
        {
            setEmail(email);
        }
    } while (!validateEmail(email));
}

void Employee::setAddressFromUserInput() {
    std::cout << "Enter Address: ";
    std::cin.ignore();
    std::getline(std::cin, address);
    setAddress(address);
}

void Employee::setGenderFromUserInput() {
    std::cout << "Enter Gender (Male, Female, Other): ";
    std::cin >> gender;
    setGender(gender);
}

void Employee::setDojFromUserInput() {
    bool validInput = false;
    do {
        std::cout << "Enter Date of Joining (DD-MM-YYYY): ";
        std::cin >> doj;
        if (!validateDateOfBirth(doj)) {
            std::cout << "Invalid date format. Please enter the date in DD-MM-YYYY format.\n";
        }
        else {
            validInput = true;
            setDoj(doj);
        }
    } while (!validInput);
}

void Employee::setWLocationFromUserInput() {
    std::cout << "Enter Work Location: ";
    std::cin >> w_location;
    setWLocation(w_location);
}

void Employee::setManagerIdFromUserInput() {
    std::cout << "Enter Manager ID: ";
    std::cin >> manager_id;
    setManagerId(manager_id);
}

void Employee::setDepartmentIdFromUserInput() {
    std::cout << "Enter Department ID: ";
    std::cin >> department_id;
    setDepartmentId(department_id);
}



void Employee::insertEmployee() { 
    
    std::cout << "Enter Employee Details:\n";

    setUserData();

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
 
     if (db_emp.executeQuery(insertQuery))
        std::cout << "Inserted Employee Succesfully ! \n";
    else
        std::cout<<db_emp.getError()<<"\n";

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
            if (db_emp.executeQuery(deleteQuery))
                std::cout << "Employee Deleted Succesfully ! \n";
            else
                std::cout << db_emp.getError() << "\n";
            break;
        case 2:
            setFirstnameFromUserInput();
            deleteQuery = "DELETE FROM Employee WHERE firstname = '" + getFirstname()+ "'";
            if (db_emp.executeQuery(deleteQuery))
                std::cout << "Employee Deleted Succesfully ! \n";
            else
                std::cout << db_emp.getError() << "\n";
            break;

        case 3:
            setEmailFromUserInput();
            deleteQuery = "DELETE FROM Employee WHERE email = '" + getEmail() + "'";
            if (db_emp.executeQuery(deleteQuery))
                std::cout << "Employee Deleted Succesfully ! \n";
            else
                std::cout << db_emp.getError() << "\n";
            break;

        case 4:
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 4.\n";
            break;
        }
    }
};

void Employee::updateEmployee() {
    std::string updateQuery{};
    int idToUpdate;
    bool flag = true;

    std::cout << "Enter the ID of the employee you want to update: ";
    std::cin >> idToUpdate;
    if (!db_emp.isIdExist(idToUpdate, "employee")) {
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
            if (db_emp.executeQuery(updateQuery))
                std::cout << "Employee information updated successfully!\n";
            else
                std::cout << "Failed to update employee information: " << db_emp.getError() << "\n";
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

            if (!db_emp.executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << db_emp.getError() << std::endl;
            }
            break;
        case 2:
            setIdFromUserInput();
            selectQuery = "SELECT * FROM Employee WHERE id = " + std::to_string(getId());
            if (!db_emp.executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << db_emp.getError() << std::endl;
            }
            break;
        case 3:
            setFirstnameFromUserInput();
            selectQuery = "SELECT * FROM Employee WHERE firstname = '" + getFirstname() + "'";
            if (!db_emp.executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << db_emp.getError() << std::endl;
            }
            break;

        case 4:
            setEmailFromUserInput();
            selectQuery = "SELECT * FROM Employee WHERE email = '" + getEmail() + "'";
            if (!db_emp.executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << db_emp.getError() << std::endl;
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

    if (!db_emp.open()) {
        std::cerr << "Error opening database: " << db_emp.getError() << std::endl;
       
    }
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
            std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
            break;
        }
    }
}
