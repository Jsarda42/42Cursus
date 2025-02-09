#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", 25, 5) , target_(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& cpy) : AForm(cpy), target_(cpy.target_) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& rhs) {
	if (this != &rhs)
		*this = rhs;
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const {
	if (!isSigned_)
		throw NotSignedExecption();
	if (executor.getGrade() > getExecGrade()) {
		throw GradeTooLowException();
	}
	else {
		std::cout << target_ << " has been pardoned by Zaphod Beeblebrox" << std::endl;
	}
}
