#include "Intern.hpp"

Intern::Intern(void) {}

Intern::Intern(const Intern &cpy)
{
	*this = cpy;
}

Intern &Intern::operator=(const Intern &rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

Intern::~Intern(void) {}

AForm *Intern::makeForm(const std::string &formName, const std::string &target) const
{
	int formIndex = 0;
	std::string forms[] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};
	while (formIndex < 3 && formName != forms[formIndex])
		formIndex++;

	switch (formIndex) {
		case 0:
			std::cout << "<intern created> " << formName << std::endl;
			return (new ShrubberyCreationForm(target));
		case 1:
			std::cout << "<intern created> " << formName << std::endl;
			return (new RobotomyRequestForm(target));
		case 2:
			std::cout << "<intern created> " << formName << std::endl;
			return (new PresidentialPardonForm(target));
	default:
		std::cerr << "Error: Form '" << formName << "' does not exist." << std::endl;
		return (NULL);
	}
}
