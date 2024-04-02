#pragma once

#include "../Department.h"
class Department;
using namespace Utility;
class DepartmentController {
public:
    static bool insertDepartmentController(Department&);
    static bool deleteDepartmentController(Department&, DepartmentAttribute);
    static bool updateDepartmentController(Department&, DepartmentAttribute);
    static bool viewDepartmentController(Department&, DepartmentViewAttribute);
};
