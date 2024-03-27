#include <iostream>
#include<filesystem>
#include "include/database.h"
#include "include/MenuControler.h"
#include "include/Auth.h"


int main() {
	std::cout << "--------------------Welcome To Employee Database Management System---------------------" << std::endl;

	if (Auth::authUser()) {
		std::filesystem::path dbPath = "employee.db";
		if (!Database::getInstance().open(dbPath)) {
			std::cerr << "Error opening database: " << Database::getInstance().getError() << std::endl;
			return 1;
		}
		system("cls");
		databaseInit();
		Database::getInstance().close();

	}

	return 0;
}
