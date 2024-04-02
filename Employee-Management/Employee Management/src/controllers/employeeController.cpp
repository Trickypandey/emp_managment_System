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
	if (Database::getInstance().executeQuery(insertQueryEmployee) && SalaryController::insertSalaryController(employee.getSalary())) {
		std::cout << "Employee Inserted Successfully ! \n\n";
		return employee.getId();
	}
	else {
		std::cout << Database::getInstance().getError() << "\n\n";
		std::cout << "Employee Insertion Failed! \n\n";
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


bool EmployeeController::updateEmployee(Employee& employee, EmployeeAttribute attribute) {
	std::string updateQuery;

	switch (attribute) {
		case EmployeeAttribute::FIRST_NAME:
			updateQuery = generateUpdateQuery("Employee", "firstname", employee.getFirstname(), employee.getId());
			break;
		case EmployeeAttribute::LAST_NAME:
			updateQuery = generateUpdateQuery("Employee", "lastname", employee.getLastname(), employee.getId());
			break;
		case EmployeeAttribute::DATE_OF_BIRTH:
			updateQuery = generateUpdateQuery("Employee", "dob", employee.getDob(), employee.getId());
			break;
		case EmployeeAttribute::MOBILE_NUMBER:
			updateQuery = generateUpdateQuery("Employee", "mobile", employee.getMobile(), employee.getId());
			break;
		case EmployeeAttribute::EMAIL_ADDRESS:
			updateQuery = generateUpdateQuery("Employee", "email", employee.getEmail(), employee.getId());
			break;
		case EmployeeAttribute::ADDRESS:
			updateQuery = generateUpdateQuery("Employee", "address", employee.getAddress(), employee.getId());
			break;
		case EmployeeAttribute::GENDER:
			updateQuery = generateUpdateQuery("Employee", "gender", employee.getGender(), employee.getId());
			break;
		case EmployeeAttribute::DATE_OF_JOINING:
			updateQuery = generateUpdateQuery("Employee", "doj", employee.getDoj(), employee.getId());
			break;
		case EmployeeAttribute::WORK_LOCATION:
			updateQuery = generateUpdateQuery("Employee", "w_location", employee.getWLocation(), employee.getId());
			break;
		case EmployeeAttribute::MANAGER_ID:
			updateQuery = generateUpdateQuery("Employee", "manager_id", std::to_string(employee.getManagerId()), employee.getId());
			break;
		case EmployeeAttribute::DEPARTMENT_ID:
			updateQuery = generateUpdateQuery("Employee", "department_id", std::to_string(employee.getDepartmentId()), employee.getId());
			break;
		default:
			break;
	}

	if (!updateQuery.empty()) {
		if (Database::getInstance().executeQuery(updateQuery)) {
			int changes = sqlite3_changes(Database::getInstance().db);
			std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
			if (changes != 0) {
				std::cout << "\033[32mEmployee Updated Successfully ! \033[0m\n\n";
				Log::getInstance().Info("Employee Updated for id : ", employee.getId());
				return true;
			}
		}
		else {
			std::cout << "Employee Updation Failed ! \033[0m\n\n";
			std::cout << Database::getInstance().getError() << "\n";
		}
	}
	return false;
}

void EmployeeController::viewEmployee(Employee& employee , EmployeeViewAttribute attribute) {
	std::string selectQuery;
	switch (attribute)
	{
	case Utility::EmployeeViewAttribute::ALL:
		selectQuery = generateSelectQuery("Employee");
		break;
	case Utility::EmployeeViewAttribute::ID:
		selectQuery = generateSelectQuery("Employee" , "id = " + std::to_string(employee.getId()));
		break;
	case Utility::EmployeeViewAttribute::FIRSTNAME:
		selectQuery = generateSelectQuery("Employee", "firstname = " + employee.getFirstname());
		break;
	case Utility::EmployeeViewAttribute::EMAIL:
		selectQuery = generateSelectQuery("Employee" , "email like" + employee.getEmail());
		break;
	default:
		break;
	}

	if (Database::getInstance().executeQueryCallback(selectQuery)) {
		Log::getInstance().Info("Department Viewed for " + selectQuery);
	}
	else {
		std::cout << Database::getInstance().getError() << "\n";
		
	}
}
