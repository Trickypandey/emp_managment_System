#pragma once

#include "../Employee.h"
#include <optional>
class Employee;

class EmployeeController {
public:
    static std::optional<int> insertEmployee(Employee&);
    static bool deleteEmployee(int employeeId);
    static bool updateEmployee(std::string);
    static void viewEmployee(Employee&);
};