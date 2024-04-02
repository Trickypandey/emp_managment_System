#pragma once

#include "../Employee.h"
#include <optional>
class Employee;
using namespace Utility;
class EmployeeController {
public:
    static std::optional<int> insertEmployee(Employee&);
    static bool deleteEmployee(int employeeId);
    static bool updateEmployee(Employee&, EmployeeAttribute);
    static void viewEmployee(Employee&, EmployeeViewAttribute);
};