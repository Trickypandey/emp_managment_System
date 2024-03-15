#ifndef salary_flag
#define salary_flag

#include <iostream>
#include "database.h"


class Salary {
public:

    Salary() = default;
    

    int getId() const { return id; }
    float getAmount() const { return amount; }
    float getBaseSalary() const { return base_salary; }
    std::string getDate() const { return date; }
    int getBonus() const { return bonus; }

    void setId(int ID) { id = ID; }
    void setAmount(float Amount) { amount = Amount; }
    void setBaseSalary(float BaseSalary) { base_salary = BaseSalary; }
    void setDate(const std::string& Date) { date = Date; }
    void setBonus(int Bonus) { bonus = Bonus; }

    bool setSidFromUserInput();
    bool setSAmountFromUserInput();
    bool setSBaseSalaryFromUserInput();
    bool setDateFromUserInput();
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
    std::string date {};
    int bonus{};
};

#endif