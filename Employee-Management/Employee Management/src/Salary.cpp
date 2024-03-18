#include "../include/Salary.h"
using namespace Utility;

bool Salary::setSidFromUserInput() {
	if (auto input = getInput<int>("Enter Employee Id: ", "Invalid Input. Please enter Id in Int.", Validation::validateInt); input.has_value()) {
		setId(input.value());
		return true;
	}
	return false;
}

bool Salary::setSAmountFromUserInput() {
	if (auto input = getInput<float>("Enter Amount: ", "Invalid Input. Please enter a valid amount.", [](double amount) { return amount >= 0.0; }); input.has_value()) {
		setAmount(input.value());
		return true;
	}
	return false;
}

bool Salary::setSBaseSalaryFromUserInput() {
	if (auto input = getInput<float>("Enter Base: ", "Invalid Input. Please enter a valid base salary.", [](double base_salary) { return base_salary >= 0.0; }); input.has_value()) {
		setBaseSalary(input.value());
		return true;
	}
	return false;
}

bool Salary::setBonusFromUserInput() {
	if (auto input = getInput<int>("Enter Bonus: ", "Invalid Input. Please enter a valid bonus.", [](double bonus) { return bonus >= 0.0; }); input.has_value()) {
		setBonus(input.value());
		return true;
	}
	return false;
}

void Salary::insertSalary() {
	std::cout << "Insert Salary Details:\n";
	auto executionFlag = false;
	std::string insertQuery;
	
	if (setSalaryData()){
		
		insertQuery = "INSERT INTO Salary (id, amount, base_salary, bonus) VALUES ("
			+ std::to_string(id) + ", '" +
			std::to_string(amount) + "', '" +
			std::to_string(base_salary) + "', '" +
			std::to_string(bonus) + "');";
		executionFlag = true;
	}

	if(executionFlag){
		if (Database::getInstance().executeQuery(insertQuery))
			std::cout << "Inserted Salary Succesfully ! \n\n";
		else
			std::cout << Database::getInstance().getError() << "\n";
	}

};
void Salary::deleteSalary() {
	auto executionFlag = false;
	std::string deleteQuery;
	if (setSidFromUserInput()) {

		deleteQuery = "DELETE FROM Salary WHERE id = " + std::to_string(getId());
		executionFlag = false;
	}

	if(executionFlag){
		if (Database::getInstance().executeQuery(deleteQuery)) {
			int changes = sqlite3_changes(Database::getInstance().db);
			std::cout << changes << " row affected \n\n";
			if (changes != 0) {
				std::cout << "Salary Deleted Succesfully ! \n\n";
			}
		}
		else
			std::cout << Database::getInstance().getError() << "\n";
	}

};
void Salary::updateSalary() {
    bool flag = true;
    bool executionFlag = false;
    std::string updateQuery{};
    int choice;

    while (flag) {
        std::cout << "Enter Salary id to update: \n";
        std::cin >> id;

        std::cout << "Please select an attribute to update:\n";
        std::cout << "1. Salary Amount\n";
        std::cout << "2. Base Salary\n";
        std::cout << "3. Bonus\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";

        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            if (setSAmountFromUserInput()) {
                updateQuery = "UPDATE Salary SET amount = '" + std::to_string(getAmount()) + "' WHERE id = " + std::to_string(id);
                executionFlag = true;
            }
            break;
        case 2:
            if (setSBaseSalaryFromUserInput()) {
                updateQuery = "UPDATE Salary SET base_salary= '" + std::to_string(getBaseSalary()) + "' WHERE id = " + std::to_string(id);
                executionFlag = true;
            }
            break;
        case 3:
            if (setBonusFromUserInput()) {
                updateQuery = "UPDATE Salary SET bonus = '" + std::to_string(getBonus()) + "' WHERE id = " + std::to_string(id);
                executionFlag = true;
            }
            break;
        case 4:
            flag = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            break;
        }

        if (executionFlag) {
            if (Database::getInstance().executeQuery(updateQuery)) {
                int changes = sqlite3_changes(Database::getInstance().db);
                std::cout << changes << " row affected \n\n";
                if (changes != 0) {
                    std::cout << "Salary Updated Successfully!\n";
                }
            }
            else {
                std::cout << "Error updating salary: " << Database::getInstance().getError() << "\n";
            }
            executionFlag = false; 
        }
    }
}

void Salary::viewSalary() {
    bool flag = true;
    bool executionFlag = false;
    std::string selectQuery{};
    int choice;

    while (flag) {
        std::cout << "Please select a column to view a Salary:\n";
        std::cout << "1. ALL\n";
        std::cout << "2. Employee Id\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";

        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            selectQuery = "SELECT id, firstname, lastname, email, amount, base_salary, bonus FROM Employee NATURAL JOIN Salary";
            executionFlag = true;
            break;
        case 2:
            if (setSidFromUserInput()) {
                selectQuery = "SELECT id, firstname, lastname, email, amount, base_salary, bonus FROM Employee NATURAL JOIN Salary WHERE id = " + std::to_string(getId());
                executionFlag = true;
            }
            break;
        case 3:
            flag = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
            break;
        }

        if (executionFlag) {
            if (!Database::getInstance().executeQueryCallback(selectQuery)) {
                std::cout << "Error viewing salary: " << Database::getInstance().getError() << std::endl;
            }
            executionFlag = false; 
        }
    }
}



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
