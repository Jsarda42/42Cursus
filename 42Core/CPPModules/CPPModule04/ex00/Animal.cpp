#include "Animal.hpp"

Animal::Animal( void ) : type_("default") {
	std::cout << "Animal " << type_ << " constructor called" << std::endl;
}

Animal::Animal( std::string type ) : type_(type) {
	std::cout << "Animal constructor called (with params)" << std::endl;
}

Animal& Animal::operator=( const Animal& rhs) {
	std::cout << "Animal operator = called" << std::endl;
	if (this != &rhs)
		this->type_ = rhs.type_;
	return (*this);
}

Animal::Animal( const Animal& cpy ) {
	std::cout << "Animal cpy constructor called" << std::endl;
	*this = cpy;
}

Animal::~Animal( void ) {
	std::cout << "Animal destructor called" << std::endl;
}

std::string Animal::getType( void ) const {
		return (type_);
}

void Animal::makeSound() const {
	std::cout << "Bruits d'animaux" << std::endl;
}
