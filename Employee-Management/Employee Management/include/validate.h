#ifndef validate_flag
#define validate_flag

#include <regex>
#include <string_view>

namespace Validation{
    inline bool validateEmail(const std::string_view& email) {
        const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return std::regex_match(email.begin(), email.end(), pattern);
    }

    inline bool validatePhoneNumber(const std::string_view& phoneNumber) {
        const std::regex pattern("\\d{10}");
        return std::regex_match(phoneNumber.begin(), phoneNumber.end(), pattern);
    }

    inline bool validateDateOfBirth(const std::string_view& dob) {
        const std::regex pattern("^(0[1-9]|[1-2][0-9]|3[0-1])-(0[1-9]|1[0-2])-(\\d{4})$");

        if (!std::regex_match(dob.begin(), dob.end(), pattern)) {
            return false;
        }

        int day = std::stoi(std::string(dob.substr(0, 2)));
        int month = std::stoi(std::string(dob.substr(3, 2)));
        int year = std::stoi(std::string(dob.substr(6, 4)));

        if (year < 1900 || year > 9999) {
            return false;
        }
        if (month < 1 || month > 12) {
            return false;
        }
        if (day < 1 || day > 31) {
            return false;
        }
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            return false;
        }
        if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                if (day > 29) {
                    return false;
                }
            }
            else {
                if (day > 28) {
                    return false;
                }
            }
        }

        return true;
    }

    inline bool validateString(const std::string_view& str) {
        const std::regex pattern(".*\\S.*");
        return std::regex_match(str.begin(), str.end(), pattern);
    }

    inline bool validateInt(const int& num) {
       
        std::string str = std::to_string(num);
        static const std::regex pattern("^[1-9]\\d*$");
        return std::regex_match(str, pattern);
    }

    inline bool validateStringAndInt(const std::string_view str) {
        const std::regex pattern("[a-zA-Z].*\\d|\\d.*[a-zA-Z]");
        return std::regex_match(str.begin(), str.end(), pattern);
    }
}

#endif
