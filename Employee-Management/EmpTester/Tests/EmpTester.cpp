#include "../pch.h"
#include "../Fixtures/EmpFixture.h"
#include "include/controllers/employeeController.h"



TEST_F(employeeFixer, AttributeEmployeeTest) {
	EXPECT_EQ(emp.getId(), 1301) << "Incorrect value.";
	EXPECT_EQ(emp.getFirstname(), "sourabh") << "Incorrect value.";
	EXPECT_EQ(emp.getLastname(), "pandey") << "Incorrect value.";
	EXPECT_EQ(emp.getDob(), "01-01-1990") << "Incorrect value.";
}

TEST_F(employeeFixer, InsertEmployeeTest) {
	EXPECT_TRUE(EmployeeController::insertEmployee(emp)) << "Error department insert";
	EXPECT_TRUE(EmployeeController::insertEmployee(emp2)) << "Error department insert";
}

//TEST_F(employeeFixer, UpdateEmployeeTest) {
//	EXPECT_TRUE(EmployeeController::updateEmployeeController(emp2, "dob")) << "Error department update";
//}
//
//TEST_F(employeeFixer, DeleteEmployeeTest) {
//	EXPECT_TRUE(EmployeeController::deleteEmployeeController(emp1, "id")) << "Error department delete";
//}



