#include "../include/Salary.h"
using namespace Utility;

bool Salary::setSidFromUserInput(std::optional<int> sid) {
    if (sid.has_value())
    {
        setId(sid.value());
        return true;
    }
    else if(auto input = getInput<int>("Enter Employee Id: ", "Invalid Input. Please enter Id in Int.", Validation::validateInt); input.has_value()) {
		setId(input.value());
		return true;
	}
	return false;
}

//bool Salary::setSAmountFromUserInput() {
//	if (auto input = getInput<float>("Enter Amount: ", "Invalid Input. Please enter a valid amount.", [](double amount) { return amount >= 0.0; }); input.has_value()) {
//		setAmount(input.value());
//		return true;
//	}
//	return false;
//}

bool Salary::setSBaseSalaryFromUserInput() {
	if (auto input = getInput<float>("Enter Base: ", "Invalid Input. Please enter a valid base salary.", [](double base_salary) { return base_salary >= 0.0; }); input.has_value()) {
		setBaseSalary(input.value());
		return true;
	}
	return false;
}

bool Salary::setBonusFromUserInput() {
	if (auto input = getInput<int>("Enter Bonus: ", "Invalid Input. Please enter a valid bonus.", [](double bonus) { return bonus >= 0.0; }); input.has_value()) {
		setBonus(input.value());
		return true;
	}
	return false;
}

void Salary::insertSalary() {
	std::cout << "Insert Salary Details:\n";
	
	if (setSalaryData()){
        if (Database::getInstance().isIdExist(getId(),"Employee"))
        {
            SalaryController::insertSalaryController(*this);
        }
        else
        {
            std::cout << "Employee doesn't exist\n";
        }
	}

};

void Salary::deleteSalary() {

	if (setSidFromUserInput(std::nullopt)) {
        SalaryController::deleteSalaryController(*this);
	}

};

void Salary::updateSalary() {
    bool flag = true;

    int choice;

    while (flag) {
        std::cout << "Enter Salary id to update: \n";
        std::cin >> id;

        std::cout << "Please select an attribute to update:\n";
        //std::cout << "1. Salary Amount\n";
        std::cout << "2. Base Salary\n";
        std::cout << "3. Bonus\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";

        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        /*case 1:
            if (setSAmountFromUserInput()) {
                SalaryController::updateSalaryController(*this, Utility::SalaryAttribute::AMOUNT);
            }
            break;*/
        case 2:
            if (setSBaseSalaryFromUserInput()) {
                
                SalaryController::updateSalaryController(*this, Utility::SalaryAttribute::BASE_SALARY);
                flag = false;
            }
            break;
        case 3:
            if (setBonusFromUserInput()) {
                
                SalaryController::updateSalaryController(*this, Utility::SalaryAttribute::BONUS);
                flag = false;
            }
            break;
        case 4:
            flag = false;
            system("cls");
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

void Salary::viewSalary() {
    bool flag = true;
    bool executionFlag = false;
    std::string selectQuery{};
    int choice;

    while (flag) {
        std::cout << "Please select a column to view a Salary:\n";
        std::cout << "1. ALL\n";
        std::cout << "2. Employee Id\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";

        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            selectQuery = "SELECT id, firstname, lastname, email, amount, base_salary, bonus FROM Employee NATURAL JOIN Salary";
            executionFlag = true;
            break;
        case 2:
            if (setSidFromUserInput(std::nullopt)) {
                selectQuery = "SELECT id, firstname, lastname, email, amount, base_salary, bonus FROM Employee NATURAL JOIN Salary WHERE id = " + std::to_string(getId());
                executionFlag = true;
            }
            break;
        case 3:
            flag = false;
            system("cls");
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
            break;
        }

        if (executionFlag) {
            SalaryController::viewSalaryController(selectQuery);
            executionFlag = false; 
        }
    }
}

void Salary::action() {
    system("cls");
    std::map<int, std::pair<std::string, std::function<void()>>> options = {
        {1, {"Insert", std::bind(&Salary::insertSalary, this)}},
        {2, {"Delete", std::bind(&Salary::deleteSalary, this)}},
        {3, {"Update", std::bind(&Salary::updateSalary, this)}},
        {4, {"View", std::bind(&Salary::viewSalary, this)}},
        {5, {"Describe", []() { Database::getInstance().describeTable("Salary"); }}},
        {6, {"Exit", []{system("cls"); }}}
    };

    executeMenu(options , "Salary Table");
}
