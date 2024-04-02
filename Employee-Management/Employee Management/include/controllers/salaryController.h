#pragma once

#include "../Salary.h"
class Salary;

class SalaryController {
public:
    static bool insertSalaryController(const Salary& salary);
    static bool deleteSalaryController(Salary& salary);
    static bool updateSalaryController(Salary& salary, Utility::SalaryAttribute attribute);
    static bool viewSalaryController(std::string selectQuery);
    //static bool incrementSalaryController(Salary& salary);
};
