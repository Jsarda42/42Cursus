#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 72, 45) , target_(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& cpy) : AForm(cpy), target_(cpy.target_) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& rhs) {
	if (this != &rhs)
		*this = rhs;
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm(void) {}

void RobotomyRequestForm::execute(const Bureaucrat& executor) const {
	if (!isSigned_)
		throw NotSignedExecption();
	if (executor.getGrade() > getExecGrade()) {
		std::cout << "The robotomy failed";
		throw GradeTooLowException();
	}
	else {
		std::cout << "Drill...Drillll...drilll " << target_ << " has been robotomized successfully 50% of the time" << std::endl;
	}
}
