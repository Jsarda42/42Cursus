#pragma once

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {

	private:
		const std::string target_;
		RobotomyRequestForm(void);

	public:
		RobotomyRequestForm(const std::string target);
		RobotomyRequestForm(const RobotomyRequestForm& cpy);
		RobotomyRequestForm& operator=(const RobotomyRequestForm& rhs);
		virtual ~RobotomyRequestForm(void);

		virtual void execute(const Bureaucrat& executor) const ;
};

std::ostream& operator<<(std::ostream& os, Bureaucrat& rhs);
