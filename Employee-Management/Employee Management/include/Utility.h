#ifndef UTILITY
#define UTILITY
#include <string_view>
#include <functional>
#include <optional>
#include <map>


namespace Utility {
    template<typename T>
    inline std::optional<T> getInput(const std::string& prompt, const std::string& errorMessage, std::function<bool(T)> validator) {
        T input;
        int count = 0;
        const int maxAttempts = 3;

        do {
            if (count >= maxAttempts) {
                std::cout << "Maximum number of attempts reached.\n";
                return std::nullopt;
            }

            std::cout << prompt;
            std::cin >> input;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << errorMessage << std::endl;
                count++;
            }
            else if (!validator(input)) {
                std::cout << errorMessage << std::endl;
                count++;
            }
            else {
                return input;
            }
        } while (true);

        return std::nullopt;
    }


    template<typename T>
    inline void executeMenu(const std::map<int, std::pair<std::string, T>>& menuOptions) {
        bool flag = true;
        int choice;

        while (flag) {
            std::cout << "Please select an action:\n";
            for (const auto& [number, prompt] : menuOptions) {
                std::cout << number << ". " << prompt.first << '\n';
            }
            std::cout << "Enter your choice (1-" << menuOptions.size() << "): ";
            std::cin >> choice;
            std::cout << '\n';

            auto it = menuOptions.find(choice);
            if (it != menuOptions.end()) {
                it->second.second();
                if (choice == menuOptions.size()) flag = false;
            }
            else {
                std::cerr << "Invalid choice. Please enter a number between 1 and " << menuOptions.size() << ".\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    inline std::string generateUpdateQuery(const std::string& tablename , const std::string& fieldName, const std::string& value, int idToUpdate) {
        return "UPDATE "+ tablename +" SET " + fieldName + " = '" + value + "' WHERE id = " + std::to_string(idToUpdate);
    }

    inline std::string generateSelectQuery(const std::string& tablename, const std::string& condition = "") {
        std::string query = "SELECT * FROM " + tablename;
        if (!condition.empty()) {
            query += " WHERE " + condition;
        }
        return query;
    }
    //selectQuery = "SELECT * FROM Department WHERE id = " + std::to_string(dept.getId());

    enum class SalaryAttribute {
        AMOUNT,
        BASE_SALARY,
        BONUS
    };


    enum class EmployeeAttribute {
        FIRST_NAME,
        LAST_NAME,
        DATE_OF_BIRTH,
        MOBILE_NUMBER,
        EMAIL_ADDRESS,
        ADDRESS,
        GENDER,
        DATE_OF_JOINING,
        WORK_LOCATION,
        MANAGER_ID,
        DEPARTMENT_ID
    };

    enum class EmployeeViewAttribute
    {
        ALL,
        ID,
        FIRSTNAME,
        EMAIL

    };

    enum class DepartmentAttribute {
        ID,
        NAME,
        MANAGER_ID,
        DESCRIPTION
    };


    enum class DepartmentViewAttribute
    {
        ALL,
        ID,
        NAME
    };

    
    enum class ManagerAttribute {
        MANGAEREXPERIENCE,
        PROJECTTITLE
    };
    
    enum class EngineerAttribute {
        PROGRAMMINGLANGUAGE,
        SPECIALIZATION
    };


}
#endif