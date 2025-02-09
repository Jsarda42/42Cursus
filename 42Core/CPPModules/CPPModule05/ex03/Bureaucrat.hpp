#pragma once

#include <iostream>
#include "AForm.hpp"

class AForm;

class Bureaucrat {

	private:
		const std::string name_;
		int grade_;
		Bureaucrat(void);

	public:
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat& cpy);
		Bureaucrat& operator=(const Bureaucrat& rhs);
		~Bureaucrat(void);
		const std::string getName(void) const;
		int getGrade(void) const;
		void incrementGrade(void);
		void decrementGrade(void);
		class GradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class FormNotSigned : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		void signForm(AForm& form) const;
		void executeForm(AForm const & form) const ;
};

std::ostream& operator<<(std::ostream& os, Bureaucrat& rhs);
