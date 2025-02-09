#include "Form.hpp"

Form::Form(const std::string name, const int signitGrade, const int execGrade) : name_(name), signitGrade_(signitGrade), execGrade_(execGrade), isSigned_(false) {
	if (signitGrade < 1)
		throw GradeTooHighException();
	if (signitGrade > 150)
		throw GradeTooLowException();
	if (execGrade < 1)
		throw GradeTooHighException();
	if (execGrade > 150)
		throw GradeTooLowException();
}

Form::Form(const Form& cpy) : name_(cpy.name_), signitGrade_(cpy.signitGrade_), execGrade_(cpy.execGrade_),  isSigned_(false) {}

Form& Form::operator=(const Form& rhs) {
	if (this != &rhs)
		*this = rhs;
	return *this;
}

Form::~Form(void) {}

const std::string Form::getName(void) const {
	return name_;
}

int Form::getSignitGrade(void) const {
	return signitGrade_;
}

bool Form::getSigned(void) const {
	return isSigned_;
}

int Form::getExecGrade(void) const {
	return execGrade_;
}

void Form::beSigned(const Bureaucrat &bureaucrat) {
	if (isSigned_ == true)
		throw AlreadySignedExecption();
	if (bureaucrat.getGrade() > signitGrade_)
		throw GradeTooLowException();
	isSigned_ = true;
}

std::ostream& operator<<(std::ostream& os, Form& rhs) {
	os	<< std::boolalpha << "Form " << rhs.getName() << ", signed: "
		<< rhs.getSigned() << ", grade to sign " << rhs.getSignitGrade()
		<< ", grade to execute " << rhs.getExecGrade() << std::endl;
	return os;
}

const char *Form::GradeTooLowException::what() const throw() {
	return ("Form grade too low! to sign");
}

const char *Form::GradeTooHighException::what() const throw() {
	return ("Form grade too high! to sign");
}

const char *Form::AlreadySignedExecption::what() const throw() {
	return ("Form is already sign");
}
