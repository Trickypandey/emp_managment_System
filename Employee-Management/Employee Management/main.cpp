#include <iostream>
#include "include/database.h"
#include "include/MenuControler.h"

int main() {

	if (!Database::getInstance().open("employee.db")) {
		std::cerr << "Error opening database: " << Database::getInstance().getError() << std::endl;
		return 1;
	}

	displayMenu();

	Database::getInstance().close();

	return 0;
}
