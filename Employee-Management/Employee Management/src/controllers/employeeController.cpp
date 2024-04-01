#include "../../include/controllers/employeeController.h"

using logs::Log;

std::optional<int> EmployeeController::insertEmployee(Employee& employee) {
	std::string managerIdString = (employee.getManagerId() != NULL) ? std::to_string(employee.getManagerId()) : "NULL";
	std::string departmentIdString = (employee.getDepartmentId() != NULL) ? std::to_string(employee.getDepartmentId()) : "NULL";

	std::string insertQueryEmployee = "INSERT INTO Employee (id, firstname, lastname, dob, mobile, email, address, gender, doj, w_location, manager_id, department_id) VALUES ("
		+ std::to_string(employee.getId()) + ", '" +
		employee.getFirstname() + "', '" +
		employee.getLastname() + "', '" +
		employee.getDob() + "', '" +
		employee.getMobile() + "', '" +
		employee.getEmail() + "', '" +
		employee.getAddress() + "', '" +
		employee.getGender() + "', '" +
		employee.getDoj() + "', '" +
		employee.getWLocation() + "', " +
		managerIdString + ", " +
		departmentIdString + ");";
	if (Database::getInstance().executeQuery(insertQueryEmployee)) {
		return employee.getId();
	}
	else {
		std::cout << Database::getInstance().getError() << "\n\n";
		return std::nullopt;
	}
};

bool EmployeeController::deleteEmployee(int employeeId) {
	std::string deleteQuery = "DELETE FROM Employee WHERE id = " + std::to_string(employeeId);

	if (Database::getInstance().executeQuery(deleteQuery)) {
		int changes = sqlite3_changes(Database::getInstance().db);
		if (changes != 0) {
			std::cout << "Employee Deleted Successfully ! \n\n";
			Log::getInstance().Info("Employee Deleted for id : ", employeeId);
			return true;
		}
	}
	else {
		std::string_view errmsg = "FOREIGN KEY constraint failed";
		if (Database::getInstance().getError() == errmsg) {
			std::string err = "Selected Employee is managing different employees, so you cannot directly delete this employee!";
			Database::getInstance().setError(err);
			Log::getInstance().Warn("Selected Employee is managing different employees: can not delete for id : ", employeeId);
		}
		std::cout << Database::getInstance().getError() << "\n\n";
	}
	return false;
}


bool EmployeeController::updateEmployee(std::string updateQuery) {
	if (Database::getInstance().executeQuery(updateQuery)) {
		int changes = sqlite3_changes(Database::getInstance().db);
		std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
		if (changes != 0) {
			return true;
		}
	}
	else {
		std::cout << Database::getInstance().getError() << "\n";
	}
	return false;

}

void EmployeeController::viewEmployee(Employee& employee) {
	bool flag = true;
	int choice;
	while (flag) {
		std::string selectQuery{};

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
			selectQuery = "SELECT * FROM Employee";
			break;
		case 2:
			employee.setIdFromUserInput();
			selectQuery = "SELECT * FROM Employee WHERE id = " + std::to_string(employee.getId());
			break;
		case 3:
			employee.setFirstnameFromUserInput();
			selectQuery = "SELECT * FROM Employee WHERE firstname = '" + employee.getFirstname() + "'";
			break;
		case 4:
			employee.setEmailFromUserInput();
			selectQuery = "SELECT * FROM Employee WHERE email = '" + employee.getEmail() + "'";
			break;
		case 5:
			flag = false;
			break;
		default:
			std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}

		if (flag && !selectQuery.empty()) {
			if (!Database::getInstance().executeQueryCallback(selectQuery)) {
				std::cerr << "Error executing query.\n";
			}
			else {
				Log::getInstance().Info(selectQuery, " : Executed.");
			}
		}
	}
}
