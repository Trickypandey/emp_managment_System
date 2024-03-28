
#ifndef emp_flag
#define emp_flag

#include <iostream>
#include <string>
#include "database.h"
#include "Utility.h"


//#include "validate.h"
//enum class Gender { Male, Female, Other };

class Employee {

public:
    Employee() = default;
   
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


    bool setIdFromUserInput();
    bool setFirstnameFromUserInput();
    bool setLastnameFromUserInput();
    bool setDobFromUserInput();
    bool setMobileFromUserInput();
    bool setEmailFromUserInput();
    bool setAddressFromUserInput();
    bool setGenderFromUserInput();
    bool setDojFromUserInput();
    bool setWLocationFromUserInput();
    bool setManagerIdFromUserInput();
    bool setDepartmentIdFromUserInput();
    



    bool insertEmployee();
    void deleteEmployee();
    void updateEmployee();
    void viewEmployee();
    void deleteById(int _id);

    void action();

private:
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


    bool setUserData() {
        if (!setIdFromUserInput() || !setFirstnameFromUserInput() || !setLastnameFromUserInput() ||
            !setDobFromUserInput() || !setMobileFromUserInput() || !setEmailFromUserInput() ||
            !setAddressFromUserInput() || !setGenderFromUserInput() || !setDojFromUserInput() ||
            !setWLocationFromUserInput() || !setManagerIdFromUserInput() || !setDepartmentIdFromUserInput()) {
            std::cout << "Error setting user data. Aborting insertion.\n";
            return false;
        }
        return true;
    }


    
};

#endif