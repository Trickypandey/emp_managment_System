
#ifndef emp_flag
#define emp_flag

#include <iostream>
#include <string>
#include "database.h"
#include "log.h"
#include "Utility.h"
#include "./controllers/employeeController.h"
#include "../include/Salary.h"

//#include "validate.h"
//enum class Gender { Male, Female, Other };
using logs::Log;
class Employee {

public:
    Employee() = default;

    Employee(int emp_id, const std::string& first, const std::string& last, const std::string& date_of_birth,
        const std::string& phone, const std::string& mail, const std::string& addr, const std::string& gen,
        const std::string& date_of_joining, const std::string& work_loc, int mgr_id, int dept_id , Salary _salary)
        : id(emp_id), firstname(first), lastname(last), dob(date_of_birth), mobile(phone), email(mail),
        address(addr), gender(gen), doj(date_of_joining), w_location(work_loc), manager_id(mgr_id),
        department_id(dept_id), salary{_salary} {}
   
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

    std::optional<int> insertEmployee();
    bool deleteEmployee(std::optional<int> _id);
    void updateEmployee(std::optional<int> id);
    void viewEmployee();

    void action();

    Salary getSalary() {
        return this->salary;
    }

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
    Salary salary;


    bool setUserData() {
        if (!setIdFromUserInput() || !setFirstnameFromUserInput() || !setLastnameFromUserInput() ||
            !setDobFromUserInput() || !setMobileFromUserInput() || !setEmailFromUserInput() ||
            !setAddressFromUserInput() || !setGenderFromUserInput() || !setDojFromUserInput() ||
            !setWLocationFromUserInput() || !setManagerIdFromUserInput() || !setDepartmentIdFromUserInput() || !salary.setSidFromUserInput(id) ||
            !salary.setSAmountFromUserInput() || !salary.setSBaseSalaryFromUserInput() || !salary.setBonusFromUserInput()) {
            std::cout << "Error setting user data. Aborting insertion.\n";
            return false;
        }
        return true;
    } 
};

#endif