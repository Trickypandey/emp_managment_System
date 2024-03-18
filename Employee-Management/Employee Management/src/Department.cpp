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
    if (auto input = getInput<int>("Enter manager ID: ", "Invalid Input. Please enter an integer.", [](int id) { return id >= 0 && Database::getInstance().isIdExist(id, "Employee"); }); input.has_value()) {
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

    std::cout << "Enter Department Details:\n";
    if (!setDepartemntData()) {
        return;
    }

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
    bool flag = true;
    while (flag)
    {

	    std::cout << "Please select a column to delete an Department:\n";
	    std::cout << "1. ID\n";
	    std::cout << "2. Dept. Name\n";
	    std::cout << "3. Exit\n";

	    std::cout << "Enter your choice (1-3): ";
	    std::cin >> choice;
	    std::cout << "\n";

	    switch (choice) {
	    case 1:
            setDidFromUserInput();
		    deleteQuery = "DELETE FROM Department WHERE id = " + std::to_string(getId());
		    break;
	    case 2:
		    setDNameFromUserInput();
		    deleteQuery = "DELETE FROM Department WHERE name = '" + getName() + "'";
		    break;
	    case 3:
            flag = false;
		    break;
	    default:
		    std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		    break;
	    }
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
            setDNameFromUserInput();
            updateQuery = "UPDATE Department SET name = '" + getName() + "' WHERE id = " + std::to_string(_id);
            
            break;
        case 2:
            setDManagerIdFromUserInput();
            updateQuery = "UPDATE Department SET manager_id= '" + std::to_string(getManagerId()) + "' WHERE id = " + std::to_string(_id);
            
            break;
        case 3:
            setDescriptionFromUserInput();
            updateQuery = "UPDATE Department SET description = '" + getDescription() + "' WHERE id = " + std::to_string(_id);
            
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

    bool flag = true;

    while (flag)
    {
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
		    setDidFromUserInput();
		    selectQuery = "SELECT * FROM Department WHERE id = " + std::to_string(getId());
		    break;
	    case 3:
		    setDNameFromUserInput();
		    selectQuery = "SELECT * FROM Department WHERE name = '" + getName() + "'";
		    break;
	    case 4:
            flag = false;
		    break;
	    default:
		    std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		    break;
	    }
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
