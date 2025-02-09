#include "AAnimal.hpp"

AAnimal::AAnimal( void ) : type_("default") {
	std::cout << "AAnimal " << type_ << " constructor called" << std::endl;
}

AAnimal::AAnimal( std::string type ) : type_(type) {
	std::cout << "AAnimal constructor called (with params)" << std::endl;
}

AAnimal& AAnimal::operator=( const AAnimal& rhs) {
	std::cout << "AAnimal operator = called" << std::endl;
	if (this != &rhs)
		this->type_ = rhs.type_;
	return (*this);
}

AAnimal::AAnimal( const AAnimal& cpy ) {
	std::cout << "AAnimal cpy constructor called" << std::endl;
	*this = cpy;
}

AAnimal::~AAnimal( void ) {
	std::cout << "AAnimal destructor called" << std::endl;
}

std::string AAnimal::getType( void ) const {
		return (type_);
}

void AAnimal::makeSound() const {
	std::cout << "Bruits d'animaux" << std::endl;
}
