#pragma once

#include "../Engineer.h"
class Engineer;

class EngineerController {
public:
    static bool insertEngineerController(Engineer& , int);
    static bool deleteEngineerController(int);
    static bool updateEngineerController(Engineer& eng, std::string attribute);
    static bool viewEngineerController(std::string selectQuery);
};