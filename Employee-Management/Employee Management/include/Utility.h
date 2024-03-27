#ifndef UTILITY
#define UTILITY
#include <string_view>
#include <functional>
#include <optional>
#include <map>


namespace Utility {
    template<typename T>
    std::optional<T> getInput(const std::string& prompt, const std::string& errorMessage, std::function<bool(T)> validator) {
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
    void executeMenu(const std::map<int, std::pair<std::string, T>>& menuOptions) {
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
}
#endif