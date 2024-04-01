#ifndef eng_flag
#define eng_flag

#include "Employee.h"
#include "database.h"
#include "Utility.h"
#include "Validate.h"

class Engineer : public Employee {
public:
	Engineer() = default;

	std::string getProgrammingLanguage() const { return programming_language; }
	std::string getSpecialization() const { return specialization; }

	void setProgrammingLanguage(const std::string& str) {
		programming_language = str;
	}
	void setSpecialization(const std::string& str) {
		specialization = str;
	}

	bool setProgLangUserInput();
	bool setSpecializationUserInput();

	void insertEngineer();
	void deleteEngineer();
	void updateEngineer();
	void viewEngineer();


	void action();

private:

	std::string programming_language{};
	std::string specialization{};
};

#endif