#include "../pch.h"
#include "../Fixtures/DepartFixture.h"
#include "include/controllers/departmentController.h"

TEST_F(departmentFixer, InsertDepartmentTest) {
    
    EXPECT_TRUE(DepartmentController::insertDepartmentController(dept1)) << "Error inserting department";
    EXPECT_TRUE(DepartmentController::insertDepartmentController(dept2)) << "Error inserting department";
    EXPECT_FALSE(DepartmentController::insertDepartmentController(dept3)) << "Error inserting department";
}

TEST_F(departmentFixer, UpdateDepartmentTest) {
   
    dept1.setName("NewName");
    EXPECT_TRUE(DepartmentController::updateDepartmentController(dept1, DepartmentAttribute::NAME)) << "Error updating department";

   
    dept1.setManagerId(1401);
    EXPECT_TRUE(DepartmentController::updateDepartmentController(dept1, DepartmentAttribute::MANAGER_ID)) << "Error updating department";

   
    dept1.setDescription("New description");
    EXPECT_TRUE(DepartmentController::updateDepartmentController(dept1, DepartmentAttribute::DESCRIPTION)) << "Error updating department";
}

TEST_F(departmentFixer, DeleteDepartmentTest) {
    
    EXPECT_TRUE(DepartmentController::deleteDepartmentController(dept1, DepartmentAttribute::ID)) << "Error deleting department";

    
    EXPECT_TRUE(DepartmentController::deleteDepartmentController(dept2, DepartmentAttribute::NAME)) << "Error deleting department";
}

TEST_F(departmentFixer, ViewDepartmentTest) {
    
    Department dummyDepartment;
    DepartmentViewAttribute viewAttribute = DepartmentViewAttribute::ALL;
    EXPECT_TRUE(DepartmentController::viewDepartmentController(dummyDepartment, viewAttribute)) << "Error viewing all departments";

   
    dummyDepartment.setId(10); 
    viewAttribute = DepartmentViewAttribute::ID;
    EXPECT_TRUE(DepartmentController::viewDepartmentController(dummyDepartment, viewAttribute)) << "Error viewing department by ID";

   
    dummyDepartment.setName("HR"); 
    viewAttribute = DepartmentViewAttribute::NAME;
    EXPECT_TRUE(DepartmentController::viewDepartmentController(dummyDepartment, viewAttribute)) << "Error viewing department by name";
}
