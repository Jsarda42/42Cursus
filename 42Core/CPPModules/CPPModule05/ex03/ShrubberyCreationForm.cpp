#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137) , target_(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& cpy) : AForm(cpy), target_(cpy.target_) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& rhs) {
	if (this != &rhs)
		*this = rhs;
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const {
	if (!isSigned_)
		throw NotSignedExecption();
	if (executor.getGrade() > getExecGrade())
		throw GradeTooLowException();
	else {
		std::ofstream file((target_ + "_shrubbery").c_str());
		if (!file.is_open()) {
			throw std::ios_base::failure("Error: Unable to open file for writing");
		}
		file << "       ###           ###           ###\n"
     << "      #o###        #o###        #o###\n"
     << "    #####o###    #####o###    #####o###\n"
     << "   #o#\\#|#/###  #o#\\#|#/###  #o#\\#|#/###\n"
     << "    ###\\|/#o#    ###\\|/#o#    ###\\|/#o#\n"
     << "     # }|{  #     # }|{  #     # }|{  #\n"
     << "       }|{          }|{          }|{\n";
		file.close();
	}
}
