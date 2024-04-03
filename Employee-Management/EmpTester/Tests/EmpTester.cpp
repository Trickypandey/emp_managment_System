#include "../pch.h"
#include "../Fixtures/EmpFixture.h"
#include "include/controllers/employeeController.h"



TEST_F(employeeFixer, AttributeEmployeeTest) {
	EXPECT_EQ(emp.getId(), 1401) << "Incorrect value.";
	EXPECT_EQ(emp.getFirstname(), "sourabh") << "Incorrect value.";
	EXPECT_EQ(emp.getLastname(), "pandey") << "Incorrect value.";
	EXPECT_EQ(emp.getDob(), "01-01-1990") << "Incorrect value.";
}

TEST_F(employeeFixer, InsertEmployeeTest) {

	// if emp is new then it should pass else fail
	EXPECT_TRUE(EmployeeController::insertEmployee(emp)) << "Error department insert";
	EXPECT_TRUE(EmployeeController::insertEmployee(emp2)) << "Error department insert";
}

TEST_F(employeeFixer, UpdateEmployeeTest) {
	// if thte manager and emp id exist then last 2  should not fail else they will fail 
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::FIRST_NAME)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::LAST_NAME)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::DATE_OF_BIRTH)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::EMAIL_ADDRESS)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::MOBILE_NUMBER)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::ADDRESS)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::DATE_OF_JOINING)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::WORK_LOCATION)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::MANAGER_ID)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::DEPARTMENT_ID)) << "Error Employee update";
	EXPECT_TRUE(EmployeeController::updateEmployee(emp, EmployeeAttribute::GENDER)) << "Error Employee update";
}


TEST_F(employeeFixer, DeleteEmployeeTest) {
	// if emp exist then pass else fail
	EXPECT_TRUE(EmployeeController::deleteEmployee(emp.getId())) << "Error Employee delete";
}

TEST_F(employeeFixer, ViewEmployeeAllTest) {
    Employee dummyEmployee;
    EmployeeViewAttribute viewAttribute = EmployeeViewAttribute::ALL;
    EXPECT_NO_THROW(EmployeeController::viewEmployee(dummyEmployee, viewAttribute)) << "Error viewing all employees";
}

TEST_F(employeeFixer, ViewEmployeeByIdTest) {
   
    Employee dummyEmployee;
    dummyEmployee.setId(1401); 
    EmployeeViewAttribute viewAttribute = EmployeeViewAttribute::ID;
    EXPECT_NO_THROW(EmployeeController::viewEmployee(dummyEmployee, viewAttribute)) << "Error viewing employee by ID";
}

TEST_F(employeeFixer, ViewEmployeeByFirstNameTest) {
  
    Employee dummyEmployee;
    dummyEmployee.setFirstname("sourabh"); 
    EmployeeViewAttribute viewAttribute = EmployeeViewAttribute::FIRSTNAME;
    EXPECT_NO_THROW(EmployeeController::viewEmployee(dummyEmployee, viewAttribute)) << "Error viewing employee by first name";
}

TEST_F(employeeFixer, ViewEmployeeByEmailTest) {
   
    Employee dummyEmployee;
    dummyEmployee.setEmail("example@example.com");
    EmployeeViewAttribute viewAttribute = EmployeeViewAttribute::EMAIL;
    EXPECT_NO_THROW(EmployeeController::viewEmployee(dummyEmployee, viewAttribute)) << "Error viewing employee by email";
}



