#pragma once

#include "AForm.hpp"
#include <fstream>
class ShrubberyCreationForm : public AForm {

	private:
		const std::string target_;
		ShrubberyCreationForm(void);

	public:
		ShrubberyCreationForm(const std::string target);
		ShrubberyCreationForm(const ShrubberyCreationForm& cpy);
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& rhs);
		virtual ~ShrubberyCreationForm(void);

		virtual void execute(const Bureaucrat& executor) const ;
};

std::ostream& operator<<(std::ostream& os, Bureaucrat& rhs);
