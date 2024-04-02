#include "../../include/controllers/engineerController.h"

using logs::Log;

bool EngineerController::insertEngineerController(Engineer& engineer , int id) {
	
	std::string insertQueryEngineer = "INSERT INTO Engineer (id, programming_language,specialization) VALUES ("
		+ std::to_string(id) + ", '" +
		engineer.getProgrammingLanguage() + "', '" +
		engineer.getSpecialization() + "'" +
		");";

	std::cout << insertQueryEngineer << "\n";
	if (Database::getInstance().executeQuery(insertQueryEngineer)) {
		std::cout << "\033[32mInserted Engineer Succesfully ! \033[0m\n\n";
		Log::getInstance().Info("Engineer Inserted for id : ", engineer.getId());
		return true;
	}
	else {
		std::cout << Database::getInstance().getError() << "\n\n";
		return false;
	}

};

bool EngineerController::deleteEngineerController(int id) {

	if (!EmployeeController::deleteEmployee(id)) {
		std::cout << Database::getInstance().getError() << "\n";
		return false;
	}

	int changes = sqlite3_changes(Database::getInstance().db);

	std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
	if (changes != 0) {
		std::cout << "\033[32mEngineer Deleted Successfully ! \033[0m\n\n";
		Log::getInstance().Info("Engineer Deleted for id : ",id);
		return true;
	}

	return false;
}

bool EngineerController::updateEngineerController(Engineer& engineer,EngineerAttribute  attribute , int _id) {
	
	std::string updateQuery;
	/*if (attribute == "programming_language") {
		updateQuery += " programming_language = '" + engineer.getProgrammingLanguage() + "'";
	}
	else if (attribute == "specialization") {
		updateQuery += " specialization= '" + engineer.getSpecialization() + "'";
	}

	updateQuery += " WHERE id = " + std::to_string(engineer.getId()) + ";";*/
	switch (attribute)	
	{
	case Utility::EngineerAttribute::PROGRAMMINGLANGUAGE:
		updateQuery = generateUpdateQuery("Engineer","programming_language",engineer.getProgrammingLanguage(),_id);
		break;
	case Utility::EngineerAttribute::SPECIALIZATION:
		updateQuery = generateUpdateQuery("Engineer","programming_language",engineer.getSpecialization(),_id);
		break;
	default:
		break;
	}
	if (Database::getInstance().executeQuery(updateQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
		if (changes != 0) {
			std::cout << "\033[32mEngineer Updated Succesfully ! \033[0m\n\n";
			Log::getInstance().Info("Engineer Updated for id : ", engineer.getId());
			return true;
		}

	}
	else {
		std::cout << Database::getInstance().getError() << "\n";
		return false;
	}
}

bool EngineerController::viewEngineerController(std::string selectQuery) {

	if (!Database::getInstance().executeQueryCallback(selectQuery)) {
		std::cout << Database::getInstance().getError() << std::endl;
		return false;
	}
	else {
		Log::getInstance().Info(selectQuery, " : Executed.");
		return true;
	}

}

