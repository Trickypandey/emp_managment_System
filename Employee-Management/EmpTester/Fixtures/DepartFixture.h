#pragma once
#include <gtest/gtest.h>
#include "include/Department.h"

class departmentFixer : public testing::Test {
protected:
    void SetUp() override {
        Database::getInstance().open("employeeTest.db");
        Database::getInstance().createTables();
    }

    Department dept1{ 10, "HR", 1301, "HR Test department" };
    Department dept2{ 11, "Test", 1301, "HR Test department" };
    Department dept3{ 11, "Test", 1301, "HR Test department" };
};
