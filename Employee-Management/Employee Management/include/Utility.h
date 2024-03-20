#ifndef UTILITY
#define UTILITY
#include <string_view>
#include <functional>
#include <optional>

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
}
#endif