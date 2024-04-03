#pragma once
#include <gtest/gtest.h>
#include "include/Engineer.h"

class engineerFixer : public testing::Test {
protected:
    void SetUp() override {
        Database::getInstance().open("employeeTest.db");
        Database::getInstance().createTables();
    }

    Salary salary1{ 1503,50000,10000 };
    Salary salary2{ 1504,50000,10000 };

    Employee emp1{ 1503, "sourabhhhhhhhhhhh", "pandey", "01-01-1990", "1234567890", "john.doe@example.com",
        "123 Main St", "Male", "01-01-2020", "New York", NULL, NULL, salary1 };
    Employee emp2{ 1504, "sourabhhhhhhhhhhh", "pandey", "01-01-1990", "1234567890", "john.doe@example.com",
        "123 Main St", "Male", "01-01-2020", "New York", NULL, NULL, salary2 };

    Engineer engineer1{ emp1, "C++", "Backend" };

    Engineer engineer2{ emp2, "Python", "Data Science" };
};
