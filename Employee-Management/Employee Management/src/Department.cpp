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

    if (Database::getInstance().executeQuery(insertQuery))
        std::cout << "Inserted Department Successfully!\n";
    else
        std::cout << Database::getInstance().getError() << "\n";

};
void Department::deleteDepartment() {
	std::string deleteQuery{};

	int choice;


	std::cout << "Please select a column to delete an Department:\n";
	std::cout << "1. ID\n";
	std::cout << "2. Dept. Name\n";
	std::cout << "3. Exit\n";

	std::cout << "Enter your choice (1-3): ";


	std::cin >> choice;
	std::cout << "\n";

	switch (choice) {
	case 1:
        setIdFromUserInput();
		deleteQuery = "DELETE FROM Department WHERE id = " + std::to_string(getId());
		break;
	case 2:
		setNameFromUserInput();
		deleteQuery = "DELETE FROM Department WHERE name = '" + getName() + "'";
		break;

	case 3:
		break;
	default:
		std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		deleteDepartment();
		break;
	}

	if (Database::getInstance().executeQuery(deleteQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << changes << " row affected \n\n";
		if (changes != 0) {
			std::cout << "Department Deleted Succesfully ! \n";
		}

	}
	else
		std::cout << Database::getInstance().getError() << "\n";

};
void Department::updateDepartment() {
    std::string updateQuery{};
    int choice;
    int _id;
    bool flag = true;

    std::cout << "Enter Department id to update: \n";
    std::cin >> _id;
    if (!Database::getInstance().isIdExist(_id, "Department")) {
        std::cerr << "Employee with ID " << _id << " does not exist in the database.\n";
        return;
    }

    while (flag) {
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
            setNameFromUserInput();
            updateQuery = "UPDATE Department SET name = '" + getName() + "' WHERE id = " + std::to_string(_id);
            flag = false; 
            break;
        case 2:
            setManagerIdFromUserInput();
            updateQuery = "UPDATE Department SET manager_id= '" + std::to_string(getManagerId()) + "' WHERE id = " + std::to_string(_id);
            flag = false;
            break;
        case 3:
            setDescriptionFromUserInput();
            updateQuery = "UPDATE Department SET description = '" + getDescription() + "' WHERE id = " + std::to_string(_id);
            flag = false;
            break;
        case 4:
            flag = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            break;
        }
    }

    if (!updateQuery.empty()) {
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

void Department::viewDepartment() {
	std::string selectQuery{};

	int choice;

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
		break;
	case 2:
		setIdFromUserInput();
		selectQuery = "SELECT * FROM Department WHERE id = " + std::to_string(getId());
		break;
	case 3:
		setNameFromUserInput();
		selectQuery = "SELECT * FROM Department WHERE name = '" + getName() + "'";
		break;
	case 4:
		break;
	default:
		std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		viewDepartment();
		break;
	}

	if (!Database::getInstance().executeQueryCallback(selectQuery)) {
		std::cout << Database::getInstance().getError() << std::endl;
	}

};

 


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
