

#include "../controllers/EmployeeController.h"
#include "../include/database.h"

bool EmployeeController::insertEmployee(const Employee& emp) {
    std::string insertQuery = generateInsertQuery(emp);

    if (Database::getInstance().executeQuery(insertQuery)) {
        std::cout << "Inserted Employee Successfully!\n";
        return true;
    }
    else {
        std::cout << Database::getInstance().getError() << "\n";
        return false;
    }
}

std::string EmployeeController::generateInsertQuery(const Employee& emp) {
    std::string insertQuery = "INSERT INTO Employee (id, firstname, lastname, dob, mobile, email, address, gender, doj, w_location, manager_id, department_id) VALUES ("
        + std::to_string(emp.getId()) + ", '" +
        emp.getFirstname() + "', '" +
        emp.getLastname() + "', '" +
        emp.getDob() + "', '" +
        emp.getMobile() + "', '" +
        emp.getEmail() + "', '" +
        emp.getAddress() + "', '" +
        emp.getGender() + "', '" +
        emp.getDoj() + "', '" +
        emp.getWLocation() + "', " +
        (emp.getManagerId() == -1 ? "null" : std::to_string(emp.getManagerId())) + ", " +
        (emp.getDepartmentId() == -1 ? "null" : std::to_string(emp.getDepartmentId())) + ");";

    return insertQuery;
}
