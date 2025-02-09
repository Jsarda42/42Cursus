#pragma once

#include "AForm.hpp"
#include "Bureaucrat.hpp"

class PresidentialPardonForm : public AForm {

	private:
		const std::string target_;
		PresidentialPardonForm(void);

	public:
		PresidentialPardonForm(const std::string target);
		PresidentialPardonForm(const PresidentialPardonForm& cpy);
		PresidentialPardonForm& operator=(const PresidentialPardonForm& rhs);
		virtual ~PresidentialPardonForm(void);

		virtual void execute(const Bureaucrat& executor) const;
};

std::ostream& operator<<(std::ostream& os, Bureaucrat& rhs);
