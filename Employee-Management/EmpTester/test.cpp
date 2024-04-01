#include "pch.h"
#include "include/database.h"
#include "include/MenuControler.h"


TEST(ValidationTest, EmailValidation) {
    EXPECT_TRUE(Validation::validateEmail("example@example.com"));
    EXPECT_TRUE(Validation::validateEmail("user123@example.com"));
    EXPECT_FALSE(Validation::validateEmail("invalid_email.com"));
    EXPECT_FALSE(Validation::validateEmail("user@.com"));
    EXPECT_FALSE(Validation::validateEmail("user@example"));
    EXPECT_FALSE(Validation::validateEmail("user@.example.com"));
}

TEST(ValidationTest, PhoneNumberValidation) {
    EXPECT_TRUE(Validation::validatePhoneNumber("1234567890"));
    EXPECT_TRUE(Validation::validatePhoneNumber("9876543210"));
    EXPECT_FALSE(Validation::validatePhoneNumber("12345"));
    EXPECT_FALSE(Validation::validatePhoneNumber("12345678901"));
    EXPECT_FALSE(Validation::validatePhoneNumber("abcdefghij"));
}

TEST(ValidationTest, DateOfBirthValidation) {
    EXPECT_TRUE(Validation::validateDateOfBirth("01-01-1990"));
    EXPECT_TRUE(Validation::validateDateOfBirth("31-12-2000"));
    EXPECT_FALSE(Validation::validateDateOfBirth("32-01-1990")); 
    EXPECT_FALSE(Validation::validateDateOfBirth("01-13-1990")); 
    EXPECT_FALSE(Validation::validateDateOfBirth("01-01-1800")); 
    EXPECT_FALSE(Validation::validateDateOfBirth("29-02-2023"));
}

TEST(ValidationTest, StringValidation) {
    EXPECT_TRUE(Validation::validateString("Hello World"));
    EXPECT_TRUE(Validation::validateString("12345"));
    EXPECT_FALSE(Validation::validateString(""));
    EXPECT_FALSE(Validation::validateString("   "));
}

TEST(ValidationTest, IntegerValidation) {
    EXPECT_TRUE(Validation::validateInt(123));
    EXPECT_TRUE(Validation::validateInt(987654));
    EXPECT_FALSE(Validation::validateInt(0));
    EXPECT_FALSE(Validation::validateInt(-123));
    //EXPECT_FALSE(Validation::validateInt(12.3)); 
}

TEST(ValidationTest, StringAndIntValidation) {
    EXPECT_TRUE(Validation::validateStringAndInt("abc123"));
    EXPECT_TRUE(Validation::validateStringAndInt("123abc"));
    EXPECT_FALSE(Validation::validateStringAndInt("abc"));
    EXPECT_FALSE(Validation::validateStringAndInt("123"));
    EXPECT_FALSE(Validation::validateStringAndInt("abc def"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
