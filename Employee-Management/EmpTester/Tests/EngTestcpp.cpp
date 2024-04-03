#include "../pch.h"
#include "../Fixtures/EngFixture.h"
#include "include/controllers/engineerController.h"

TEST_F(engineerFixer, InsertEngineerTest) {
    EXPECT_TRUE(EngineerController::insertEngineerController(engineer1, engineer1.getId())) << "Error inserting engineer";
    EXPECT_TRUE(EngineerController::insertEngineerController(engineer2, engineer2.getId())) << "Error inserting engineer";
}

TEST_F(engineerFixer, DeleteEngineerTest) {
    EXPECT_TRUE(EngineerController::deleteEngineerController(engineer1.getId())) << "Error deleting engineer";
    EXPECT_TRUE(EngineerController::deleteEngineerController(engineer2.getId())) << "Error deleting engineer";
}

TEST_F(engineerFixer, UpdateEngineerTest) {
    engineer1.setProgrammingLanguage("NewLanguage");
    EXPECT_TRUE(EngineerController::updateEngineerController(engineer1, Utility::EngineerAttribute::PROGRAMMINGLANGUAGE, engineer1.getId())) << "Error updating engineer";

    engineer2.setSpecialization("NewSpecialization");
    EXPECT_TRUE(EngineerController::updateEngineerController(engineer2, Utility::EngineerAttribute::SPECIALIZATION, engineer2.getId())) << "Error updating engineer";
}

TEST_F(engineerFixer, ViewEngineerTest) {
    std::string selectQuery = "SELECT * FROM Engineer";
    EXPECT_TRUE(EngineerController::viewEngineerController(selectQuery)) << "Error viewing engineers";
}
