#pragma once

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {

	private:
		const std::string name_;
		const int signitGrade_;
		const int execGrade_;
		bool isSigned_;
		Form(void);

	public:
		Form(const std::string name, const int signitGrade, const int execGrade);
		Form(const Form& cpy);
		Form& operator=(const Form& rhs);
		~Form(void);
		const std::string getName(void) const;
		int getSignitGrade(void) const;
		int getExecGrade(void) const;
		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class AlreadySignedExecption : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		void beSigned(const Bureaucrat &bureaucrat);
		bool getSigned() const;
};

std::ostream& operator<<(std::ostream& os, Form& rhs);
