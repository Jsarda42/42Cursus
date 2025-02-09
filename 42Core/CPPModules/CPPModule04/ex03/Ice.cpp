#include "Ice.hpp"

Ice::Ice(void) : AMateria("ice") {
	//std::cout << "Ice created!" << std::endl;
}

Ice& Ice::operator=(const Ice& rhs) {
	std::cout << "Ice assignment operator called!" << std::endl;
	if (this != &rhs) {
		*this = rhs;
	}
	return (*this);
}

Ice::Ice(const Ice& cpy) {
	std::cout << "Ice copy constructed!" << std::endl;
	this->type_ = cpy.type_;
}

Ice::~Ice(void) {
	//std::cout << "Ice destroyed!" << std::endl;
}

AMateria* Ice::clone() const {
	return (new Ice);
}

void Ice::use(ICharacter& target) {
	std::cout << "* shoots an ice bolt at " << target.getName() << "*" << std::endl;
}
