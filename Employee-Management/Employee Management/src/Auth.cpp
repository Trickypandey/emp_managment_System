#include "../include/Auth.h"
#include "../include/log.h"
#include <iostream>
#include <conio.h>
#include <string>


using namespace std;
using namespace logs;

namespace Auth {
    std::string getPassword() {
        std::string password;
        char ch;
        while (true) {
            ch = _getch();
            if (ch == '\r') {
                std::cout << std::endl;
                break;
            }
            if (ch == '\b' && !password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
            else if (ch != '\b') {
                std::cout << '*';
                password.push_back(ch);
            }
        }
        return password;
    }

    bool authUser() {
        std::string username, password;
        int tryCount = 0;

        while (tryCount < 3) {
            std::cout << "Enter Username:";
            std::getline(std::cin, username);
            std::cout << "Enter password:";
            password = getPassword();

            if (username == "admin" && password == "admin") {
                Log::getInstance().Info(username, "signed in.");
                return true;
            }
            else {
                tryCount++;
                std::cout << "Wrong Credentials!\n";
                Log::getInstance().Warn(tryCount, "attempt");
            }
        }

        if (tryCount == 3) {
            std::cout << "Maximum number of attempts reached!\n";
            Log::getInstance().Error("Maximum number of attempts reached for : ", username);
        }
        return false;
    }
}
