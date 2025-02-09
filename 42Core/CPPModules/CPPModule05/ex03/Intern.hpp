#pragma once
#include <iostream>
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern {

	public:
		Intern(void);
		Intern(const Intern& cpy);
		Intern& operator=(const Intern& rhs);
		~Intern(void);

		AForm *makeForm(const std::string& formName, const std::string &formTarget) const;
};
