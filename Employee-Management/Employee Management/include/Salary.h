#ifndef salary_flag
#define salary_flag

#include <iostream>
#include "database.h"
#include "Utility.h"
#include "Validate.h"
#include "controllers/salaryController.h"


class Salary {
public:

    Salary() = default;

    Salary(int _id, float _baseSalary ,int _bonus): id(_id), base_salary(_baseSalary), bonus(_bonus) {}
    

    int getId() const { return id; }
    float getAmount() const { return amount; }
    float getBaseSalary() const { return base_salary; }
    
    int getBonus() const { return bonus; }

    void setId(int ID) { id = ID; }
    void setAmount(float Amount) { amount = Amount; }
    void setBaseSalary(float BaseSalary) { base_salary = BaseSalary; }
    
    void setBonus(int Bonus) { bonus = Bonus; }

    bool setSidFromUserInput(std::optional<int>);
    bool setSAmountFromUserInput();
    bool setSBaseSalaryFromUserInput();
    bool setBonusFromUserInput();

    void insertSalary();
    void deleteSalary();
    void updateSalary();
    void viewSalary();

    void action();

private:

    int id{};
    float amount {};
    float base_salary {};
    int bonus{};

    bool setSalaryData() {
        if (!setSidFromUserInput(std::nullopt) || !setSAmountFromUserInput() || !setSBaseSalaryFromUserInput() ||
            !setBonusFromUserInput()) {
            std::cout << "Error setting Salary data. Aborting insertion.\n";
            return false;
        }
        return true;
    }
};

#endif