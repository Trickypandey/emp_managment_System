#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>
//#include "log.h"

namespace Auth {
    std::string getPassword();
    bool authUser();
}

#endif
