#pragma once

#include "../Manager.h"
class Manager;

class ManagerController {
public:
    static bool insertManagerController(Manager&,int);
    static bool deleteManagerController(int);
    static bool updateManagerController(Manager& manager, std::string attribute);
    static bool viewManagerController(std::string selectQuery);
};