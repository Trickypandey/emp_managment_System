#include "../pch.h"
#include "../Fixtures/ManagarFixture.h"
#include "include/controllers/managerController.h"

TEST_F(managerFixer, InsertManagerTest) {
    EXPECT_TRUE(ManagerController::insertManagerController(manager1, manager1.getId())) << "Error inserting manager";
    EXPECT_TRUE(ManagerController::insertManagerController(manager2, manager2.getId())) << "Error inserting manager";
}

TEST_F(managerFixer, DeleteManagerTest) {
    EXPECT_TRUE(ManagerController::deleteManagerController(manager1.getId())) << "Error deleting manager";
    EXPECT_TRUE(ManagerController::deleteManagerController(manager2.getId())) << "Error deleting manager";
}

TEST_F(managerFixer, UpdateManagerTest) {
    manager1.setManagementExperience(5);
    EXPECT_TRUE(ManagerController::updateManagerController(manager1, Utility::ManagerAttribute::MANGAEREXPERIENCE, manager1.getManagementExperience())) << "Error updating manager";

    manager2.setProjectTitle("NewTitle");
    EXPECT_TRUE(ManagerController::updateManagerController(manager2, Utility::ManagerAttribute::PROJECTTITLE, manager2.getId())) << "Error updating manager";
}

TEST_F(managerFixer, ViewManagerTest) {
    std::string selectQuery = "SELECT * FROM Manager";
    EXPECT_TRUE(ManagerController::viewManagerController(selectQuery)) << "Error viewing managers";
}
