#pragma once
#include<gtest/gtest.h>
#include "include/Salary.h"

class salaryFixer : public testing::Test {
protected:
	void SetUp() override {
		Database::getInstance().open("employeeTest.db");
		Database::getInstance().createTables();
	}

	Salary salary1{ 1301, 25000.0, 10000 };
	Salary salary2{ 1301, 25000.0, 10000 };

};