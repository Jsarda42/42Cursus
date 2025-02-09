#include "AForm.hpp"

AForm::AForm(const std::string name, const int signitGrade, const int execGrade) : name_(name), signitGrade_(signitGrade), execGrade_(execGrade), isSigned_(false) {
	if (signitGrade < 1)
		throw GradeTooHighException();
	if (signitGrade > 150)
		throw GradeTooLowException();
	if (execGrade < 1)
		throw GradeTooHighException();
	if (execGrade > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& cpy) : name_(cpy.name_), signitGrade_(cpy.signitGrade_), execGrade_(cpy.execGrade_),  isSigned_(false) {}

AForm& AForm::operator=(const AForm& rhs) {
	if (this != &rhs)
		*this = rhs;
	return *this;
}

AForm::~AForm(void) {}

const std::string AForm::getName(void) const {
	return name_;
}

int AForm::getSignitGrade(void) const {
	return signitGrade_;
}

bool AForm::getSigned(void) const {
	return isSigned_;
}

int AForm::getExecGrade(void) const {
	return execGrade_;
}

void AForm::beSigned(const Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() > signitGrade_)
		throw GradeTooLowException();
	isSigned_ = true;
}

std::ostream& operator<<(std::ostream& os, AForm& rhs) {
	os	<< std::boolalpha << "Form " << rhs.getName() << ", signed: "
		<< rhs.getSigned() << ", grade to sign " << rhs.getSignitGrade()
		<< ", grade to execute " << rhs.getExecGrade() << std::endl;
	return os;
}

const char *AForm::GradeTooLowException::what() const throw() {
	return ("<Form> grade too low!");
}

const char *AForm::GradeTooHighException::what() const throw() {
	return ("<Form> grade too high!");
}

const char *AForm::AlreadySignedExecption::what() const throw() {
	return ("<Form> is already sign");
}

const char *AForm::NotSignedExecption::what() const throw() {
	return ("<Form> is not signed");
}
