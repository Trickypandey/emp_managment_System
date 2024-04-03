#pragma once
#include<gtest/gtest.h>
#include "include/Manager.h"

class managerFixer : public testing::Test {
protected:
	void SetUp() override {
		Database::getInstance().open("employeeTest.db");
		Database::getInstance().createTables();
	}

	Salary salary1{ 1501,50000,10000 };
	Salary salary2{ 1502,50000,10000 };

	Employee emp{ 1501, "sourabhhhhhhhhhhh", "pandey", "01-01-1990", "1234567890", "john.doe@example.com",
		"123 Main St", "Male", "01-01-2020", "New York", NULL, NULL, salary1 };
	Employee emp1{ 1502, "sourabhhhhhhhhhhh", "pandey", "01-01-1990", "1234567890", "john.doe@example.com",
		"123 Main St", "Male", "01-01-2020", "New York", NULL, NULL, salary2 };

	Manager manager1{ emp,3,"TitleTest" };

	Manager manager2{ emp1,3,"TitleTestUpdated" };

	//Salary salary1{ 1001,50000,10000 };

};