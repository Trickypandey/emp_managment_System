#pragma once
#include "../pch.h"
#include "gtest/gtest.h"
#include "include/Employee.h"
#include "include/Salary.h"

class employeeFixer : public testing::Test {
protected:
    void SetUp() override {
        Database::getInstance().open("employeeTest.db");
        Database::getInstance().createTables();
    }
    Salary salary1{ 1401,50000,10000 };
    Salary salary2{ 1501,50000,10000 };

    Employee emp{ 1401, "sourabhhhhhhhhhhh", "pandey", "01-01-1990", "1234567890", "john.doe@example.com",
        "123 Main St", "Male", "01-01-2020", "New York", NULL, NULL, salary1 };
    Employee emp2{ 1501, "TEMP", "TEMP", "01-01-1990", "1234567890", "john.doe@example.com",
        "123 Main St", "Male", "01-01-2020", "New York", NULL, NULL, salary2 };
};