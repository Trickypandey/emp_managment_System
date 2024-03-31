#include <iostream>
#include<filesystem>
#include "include/database.h"
#include "include/MenuControler.h"
#include "include/Auth.h"
#include "include/log.h"
using logs::Log;

// this is working
int main() {

	if (Auth::authUser()) {
		std::filesystem::path dbPath = "employee.db";
		if (!Database::getInstance().open(dbPath)) {
			std::cerr << "Error opening database: " << Database::getInstance().getError() << std::endl;
			return 1;
		}
		Log::getInstance().Info("Database Opened.");
		system("cls");
		std::cout << "--------------------Welcome To Employee Database Management System---------------------" << std::endl;
		databaseInit();
		Database::getInstance().close();

	}

	return 0;
}
