#pragma once

#include "../Manager.h"
class Manager;
using namespace Utility;
class ManagerController {
public:
    static bool insertManagerController(Manager&,int);
    static bool deleteManagerController(int);
    static bool updateManagerController(Manager&,ManagerAttribute,int );
    static bool viewManagerController(std::string selectQuery);
};