#include "pch.h"
#include "include/database.h"
#include "include/MenuControler.h"


TEST(TestExample, Test_testfunc) {
	//ASSERT_EQ(Validation::validateInt(8.55), true);
	EXPECT_FALSE(Validation::validateInt('as'));
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}