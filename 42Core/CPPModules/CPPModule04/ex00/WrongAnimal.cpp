#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal( void ) : type_("default") {
	std::cout << "WrongAnimal default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal( std::string type ) : type_(type) {
	std::cout << "WrongAnimal constructor called (with params)" << std::endl;
}

WrongAnimal& WrongAnimal::operator=( const WrongAnimal& rhs) {
	std::cout << "WrongAnimal operator = called" << std::endl;
	if (this != &rhs)
		this->type_ = rhs.type_;
	return (*this);
}

WrongAnimal::WrongAnimal( const WrongAnimal& cpy ) {
	std::cout << "WrongAnimal cpy constructor called" << std::endl;
	*this = cpy;
}

WrongAnimal::~WrongAnimal( void ) {
	std::cout << "WrongAnimal destructor called" << std::endl;
}

std::string WrongAnimal::getType( void ) const {
		return (type_);
}

void WrongAnimal::makeSound( void ) const {
	std::cout << "faux miaou" << std::endl;
}
