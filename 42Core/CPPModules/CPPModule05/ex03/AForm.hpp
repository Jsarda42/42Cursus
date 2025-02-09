#pragma once

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {

	private:
		const std::string name_;
		const int signitGrade_;
		const int execGrade_;

	public:
		bool isSigned_;
		AForm(const std::string name, const int signitGrade, const int execGrade);
		AForm(const AForm& cpy);
		AForm& operator=(const AForm& rhs);
		virtual ~AForm(void);
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
		class NotSignedExecption : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		void beSigned(const Bureaucrat &bureaucrat);
		bool getSigned() const;
		virtual void execute(const Bureaucrat& executor) const = 0;
};

std::ostream& operator<<(std::ostream& os, AForm& rhs);
