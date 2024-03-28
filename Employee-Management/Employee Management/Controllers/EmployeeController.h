

#ifndef EMPLOYEE_CONTROLLER_H
#define EMPLOYEE_CONTROLLER_H

#include <string>
#include "../include/employee.h" 
class Employee;
class EmployeeController {
public:
        static bool insertEmployee(const Employee&  emp);
        static std::string generateInsertQuery(const Employee& emp);
};

#endif 
