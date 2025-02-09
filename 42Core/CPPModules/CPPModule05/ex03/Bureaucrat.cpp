#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(std::string name, int grade) : name_(name), grade_(grade){
	if (grade < 1)
		throw GradeTooHighException();
	if (grade > 150)
		throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& cpy) : name_(cpy.name_){
	grade_ = cpy.grade_;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& rhs) {
	if (this != &rhs)
		*this = rhs;
	return *this;
}

Bureaucrat::~Bureaucrat(void) {}

const std::string Bureaucrat::getName(void) const {
	return (name_);
}

int Bureaucrat::getGrade(void) const {
	return (grade_);
}

void Bureaucrat::incrementGrade(void) {
	if (grade_ == 1)
		throw GradeTooHighException();
	grade_--;
}

void Bureaucrat::decrementGrade(void) {
	if (grade_ == 150)
		throw GradeTooLowException();
	grade_ ++;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}

std::ostream& operator<<(std::ostream& os, Bureaucrat& rhs) {
	os << rhs.getName() << ", bureaucrat grade " << rhs.getGrade() << std::endl;
	return os;
}

void	Bureaucrat::signForm(AForm& form) const {
	try {
		form.beSigned(*this);
		std::cout << name_ << " signs " << form.getName() << std::endl;
	}
	catch (std::exception& e) {
		std::cout	<< name_ << " cannot sign " << form.getName() << " because "
					<< e.what() << std::endl;
	}
}

const char *Bureaucrat::FormNotSigned::what() const throw()
{
	return ("The form need to be signed!");
}

void Bureaucrat::executeForm(AForm const & form) const {
	try {
		form.execute(*this);
		std::cout << name_ << " executes " << form.getName() << std::endl;
	}
	catch (std::exception& e) {
		std::cout	<< name_ << " cannot execute " << form.getName() << " because "
					<< e.what() << std::endl;
	}
}
