#pragma once
#include <iostream>
#include <map>
#include "Utility.h"
#include "../include/database.h"
#include "../include/Employee.h"
#include "../include/Engineer.h"
#include "../include/Manager.h"
#include "../include/Salary.h"
#include "../include/department.h"

void manipulateDB() {
	std::map<int, std::pair<std::string, std::function<void()>>> tableOptions = {
		{1, {"Employee", []() { system("cls"); Employee employee; employee.action(); }}},
		{2, {"Department", []() { system("cls"); Department department; department.action(); }}},
		{3, {"Salary", []() { system("cls"); Salary salary; salary.action(); }}},
		{4, {"Engineer", []() { system("cls"); Engineer engineer; engineer.action(); }}},
		{5, {"Manager", []() { system("cls"); Manager manager; manager.action(); }}},
		{6, {"Main Menu", []() {system("cls"); }}}
	};

	Utility::executeMenu(tableOptions);


}


void databaseInit() {
	std::map<int, std::pair<std::string, std::function<void()>>> menuOptions = {
		{1, {"Create Table", []() { Database::getInstance().createTableQuery(); }}},
		{2, {"Show Tables", []() { Database::getInstance().showTables(); }}},
		{3, {"Manipulate Existing Database", []() { manipulateDB(); }}},
		{4, {"Delete Table", []() { Database::getInstance().deleteTableQuery(); }}},
		{5, {"Run SQL Query", []() { Database::getInstance().useSqlQuery(); }}},
		{6, {"Backup Existing Database", [] {
			std::vector<std::string> tables = {"Employee", "Engineer", "Manager", "Salary", "Department"};
			for (const auto& table : tables) {
				std::string backupFilePath = "backup/" + table + ".csv";
				Database::getInstance().export_to_csv(table, backupFilePath);
			}
			std::cout << "All Tables Backed up successfully.\n";
		}}},
		{7, {"Exit", []() {}}}
	};

	Utility::executeMenu(menuOptions);
}