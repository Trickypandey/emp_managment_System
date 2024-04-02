#include "../../include/controllers/departmentController.h"

using logs::Log;

bool DepartmentController::insertDepartmentController(Department& dept) {

	std::string managerIdString = (dept.getManagerId() != NULL) ? std::to_string(dept.getManagerId()) : "NULL";

	std::string insertQuery = "INSERT INTO Department (id, name, manager_id, description) VALUES ("
		+ std::to_string(dept.getId()) + ", '" +
		dept.getName() + "', " +
		managerIdString + ", '" +
		dept.getDescription() + "');";

	if (Database::getInstance().executeQuery(insertQuery)) {
		std::cout << "\033[32mInserted Department Successfully! \033[0m\n\n";
		Log::getInstance().Info("Department Inserted for id : ", dept.getId());
		return true;
	}
	else {
		std::cout << Database::getInstance().getError() << "\n";
		return false;
	}
};

bool DepartmentController::deleteDepartmentController(Department& dept,DepartmentAttribute attribute) {
	std::string deleteQuery{};
	if (attribute == DepartmentAttribute::ID) {
		deleteQuery = "DELETE FROM Department WHERE id = " + std::to_string(dept.getId());
	}
	else {
		deleteQuery = "DELETE FROM Department WHERE name = '" + dept.getName() + "'";
	}

	if (Database::getInstance().executeQuery(deleteQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
		if (changes != 0) {
			std::cout << "\033[32mDepartment Deleted Succesfully ! \033[0m\n\n";
			Log::getInstance().Info("Department Deleted for id : ", dept.getId());
			return true;
		}

	}
	else {
		std::cout << Database::getInstance().getError() << "\n";
		return false;
	}
}

bool DepartmentController::updateDepartmentController(Department& dept, DepartmentAttribute attribute) {
	std::string updateQuery;

	switch (attribute)
	{
		case Utility::DepartmentAttribute::NAME:
			updateQuery = generateUpdateQuery("Department", "name", dept.getName(), dept.getId());
			break;
		case Utility::DepartmentAttribute::MANAGER_ID:
			updateQuery = generateUpdateQuery("Department", "manager_id", std::to_string(dept.getManagerId()), dept.getId());
			break;
		case Utility::DepartmentAttribute::DESCRIPTION:
			updateQuery = generateUpdateQuery("Department", "description", dept.getDescription(), dept.getId());
			break;
		default:
			break;
	}
	

	if (Database::getInstance().executeQuery(updateQuery)) {
		int changes = sqlite3_changes(Database::getInstance().db);
		std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
		if (changes != 0) {
			std::cout << "\033[32mDepartment Updated Successfully ! \033[0m\n\n";
			Log::getInstance().Info("Department Updated for id : ", dept.getId());
			return true;
		}
	}
	else {
		std::cout << Database::getInstance().getError() << "\n";
		std::cout << "\033[32m Department Updation Failed! \033[0m\n\n";
		return false;
	}
}

bool DepartmentController::viewDepartmentController(Department& dept, DepartmentViewAttribute condition) {

	std::string selectQuery;
	

	switch (condition)
	{
	case Utility::DepartmentViewAttribute::ALL:
		selectQuery = generateSelectQuery("Department");
		selectQuery = "SELECT * FROM Department";
		break;
	case Utility::DepartmentViewAttribute::ID:
		selectQuery = generateSelectQuery("Department", "id = " + std::to_string(dept.getId()));
		//selectQuery = "SELECT * FROM Department WHERE id = " + std::to_string(dept.getId());
		break;
	case Utility::DepartmentViewAttribute::NAME:
		//selectQuery = generateSelectQuery("Department", "name = " + dept.getName());
		selectQuery = "SELECT * FROM Department WHERE name = '" + dept.getName() + "'";

		break;
	default:
		break;
	}
	
	if (Database::getInstance().executeQueryCallback(selectQuery)) {
		Log::getInstance().Info("Department Viewed for " + selectQuery );
	}
	else {
		std::cout << Database::getInstance().getError() << "\n";
		return false;
	}
}
