#include <iostream>
#include<filesystem>
#include "include/database.h"
#include "include/MenuControler.h"
#include "include/Auth.h"
#include "include/log.h"
using logs::Log;

// this is working
int main() {
	std::cout << "\033[32m -------------------- username = admin && password = admin ---------------------\033[0m\n\n";
	if (Auth::authUser()) {
		std::filesystem::path dbPath = "employee.db";
		if (!Database::getInstance().open(dbPath)) {
			std::cerr << "Error opening database: " << Database::getInstance().getError() << std::endl;
			return 1;
		}
		Log::getInstance().Info("Database Opened.");
		system("cls");
		std::cout << "\033[32m -------------------- Welcome To Employee Database Management System ---------------------\033[0m\n\n";
		databaseInit();
		Database::getInstance().close();

	}

	return 0;
}
