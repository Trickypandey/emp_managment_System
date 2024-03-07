
#ifndef emp_flag
#define emp_flag

#include <iostream>
#include <string>
#include<vector>
#include "database.h"


//#include "validate.h"
//enum class Gender { Male, Female, Other };

class Employee {

public:
    Employee() = default;
    Employee(const Database& db) {
        db_emp = db;
    }

    
    int getId() const { return id; }
    std::string getFirstname() const { return firstname; }
    std::string getLastname() const { return lastname; }
    std::string getDob() const { return dob; }
    std::string getMobile() const { return mobile; }
    std::string getEmail() const { return email; }
    std::string getAddress() const { return address; }
    std::string getGender() const { return gender; }
    std::string getDoj() const { return doj; }
    std::string getWLocation() const { return w_location; }
    int getManagerId() const { return manager_id; }
    int getDepartmentId() const { return department_id; }

    void setId(int nid) {
        id = nid;
    }
    
    void setFirstname(const std::string& firstName) {
        firstname = firstName;
    }

    void setLastname(const std::string& lastName) {
        lastname = lastName;
    }

    void setDob(const std::string& dateOfBirth) {
        dob = dateOfBirth;
    }

    void setMobile(const std::string& mobileNumber) {
        mobile = mobileNumber;
    }

    void setEmail(const std::string& emailAddress) {
        email = emailAddress;
    }

    void setAddress(const std::string& addressValue) {
        address = addressValue;
    }

    void setGender(const std::string& genderValue) {
        gender = genderValue;
    }

    void setDoj(const std::string& dateOfJoining) {
        doj = dateOfJoining;
    }

    void setWLocation(const std::string& workLocation) {
        w_location = workLocation;
    }

    void setManagerId(int managerIdValue) {
        manager_id = managerIdValue;
    }

    void setDepartmentId(int departmentIdValue) {
        department_id = departmentIdValue;
    }


    void setIdFromUserInput();
    void setFirstnameFromUserInput();
    void setLastnameFromUserInput();
    void setDobFromUserInput();
    void setMobileFromUserInput();
    void setEmailFromUserInput();
    void setAddressFromUserInput();
    void setGenderFromUserInput();
    void setDojFromUserInput();
    void setWLocationFromUserInput();
    void setManagerIdFromUserInput();
    void setDepartmentIdFromUserInput();
    



    void insertEmployee();
    void deleteEmployee();
    void updateEmployee();
    void viewEmployee();

    void action();

private:
    Database db_emp;
    int id{};
    std::string firstname{};
    std::string lastname{};
    std::string dob{};
    std::string mobile{};
    std::string email{};
    std::string address{};
    std::string gender{};
    std::string doj{};
    std::string w_location{};
    int manager_id{};
    int department_id{};


    std::string  generateUpdateQuery(const std::string& fieldName, const std::string& value, int idToUpdate);

    void setUserData() {
        setIdFromUserInput();
        setFirstnameFromUserInput();
        setLastnameFromUserInput();
        setDobFromUserInput();
        setMobileFromUserInput();
        setEmailFromUserInput();
        setAddressFromUserInput();
        setGenderFromUserInput();
        setDojFromUserInput();
        setWLocationFromUserInput();
        setManagerIdFromUserInput();
        setDepartmentIdFromUserInput();
    }
};

#endif