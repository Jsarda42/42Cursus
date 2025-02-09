#include "Cure.hpp"

Cure::Cure(void) : AMateria("cure") {
	//std::cout << "Cure created!" << std::endl;
}

Cure& Cure::operator=(const Cure& rhs) {
	std::cout << "Cure assignment operator called!" << std::endl;
	if (this != &rhs) {
		*this = rhs;
	}
	return (*this);
}

Cure::Cure(const Cure& cpy) {
	std::cout << "Cure copy constructed!" << std::endl;
	this->type_ = cpy.type_;
}

Cure::~Cure(void) {
	//std::cout << "Cure destroyed!" << std::endl;
}

AMateria* Cure::clone() const {
	return (new Cure);
}

void Cure::use(ICharacter& target) {
	std::cout << "* shoots an Cure bolt at " << target.getName() << "*" << std::endl;
}
