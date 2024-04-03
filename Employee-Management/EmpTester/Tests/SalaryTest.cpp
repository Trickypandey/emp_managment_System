#include "../pch.h"
#include "../Fixtures/SalaryFixture.h"
#include "include/controllers/salaryController.h"

TEST_F(salaryFixer, InsertSalaryTest) {
   
    EXPECT_TRUE(SalaryController::insertSalaryController(salary1)) << "Error inserting salary";
    EXPECT_FALSE(SalaryController::insertSalaryController(salary2)) << "Error inserting salary";
}

TEST_F(salaryFixer, UpdateSalaryTest) {
   
    salary1.setAmount(30000.0);
    EXPECT_TRUE(SalaryController::updateSalaryController(salary1, Utility::SalaryAttribute::AMOUNT)) << "Error updating salary";

  
    salary1.setBaseSalary(15000.0);
    EXPECT_TRUE(SalaryController::updateSalaryController(salary1, Utility::SalaryAttribute::BASE_SALARY)) << "Error updating salary";

   
    salary1.setBonus(5000.0);
    EXPECT_TRUE(SalaryController::updateSalaryController(salary1, Utility::SalaryAttribute::BONUS)) << "Error updating salary";
}

TEST_F(salaryFixer, DeleteSalaryTest) {
  
    EXPECT_TRUE(SalaryController::deleteSalaryController(salary1)) << "Error deleting salary";
}

TEST_F(salaryFixer, ViewSalaryTest) {
  
    std::string selectQuery = "SELECT * FROM Salary WHERE id = 1";
    EXPECT_TRUE(SalaryController::viewSalaryController(selectQuery)) << "Error viewing salary";
}
