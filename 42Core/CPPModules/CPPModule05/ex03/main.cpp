#include "Bureaucrat.hpp"
#include <iostream>
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "AForm.hpp"
#include "Intern.hpp"

void	sectionTitle(const std::string& title) {
	std::cout	<< std::endl
				<< "*** " << title << " ***"
				<< std::endl << std::endl;
}

void	testForm(const Bureaucrat& bureaucrat, AForm& form) {
	std::cout << form;
	bureaucrat.signForm(form);
	bureaucrat.executeForm(form);
}

int	main() {
	Bureaucrat	burro("Tony", 1);
	Bureaucrat	burretto("Popo", 42);
	std::cout << burro << burretto;

	try {
		{
			sectionTitle("shrubbery creation");
			ShrubberyCreationForm form("home");
			testForm(burro, form);
		}
		{
			sectionTitle("robotomy request");
			RobotomyRequestForm form("Robot");
			testForm(burro, form);
		}
		{
			sectionTitle("presidential pardon");
			PresidentialPardonForm form("Preside");
			testForm(burro, form);
		}
		PresidentialPardonForm form("Preside");
		{
			sectionTitle("execute unsigned form");
			std::cout << form;
			burro.executeForm(form);
		}
		{
			sectionTitle("too low to execute");
			burro.signForm(form);
			burretto.executeForm(form);
		}
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	{
		sectionTitle("Intern form creation");
		Intern SomeRandomIntern;
		AForm* rrf;
		AForm* rrf1;
		AForm* rrf2;
		AForm* rrf3;

		rrf = SomeRandomIntern.makeForm("ShrubberyCreationForm", "home");
		rrf1 = SomeRandomIntern.makeForm("RobotomyRequestForm", "home");
		rrf2 = SomeRandomIntern.makeForm("PresidentialPardonForm", "home");
		rrf3 = SomeRandomIntern.makeForm("wrong", "home");
		delete rrf;
		delete rrf1;
		delete rrf2;
		delete rrf3;
	}
}

