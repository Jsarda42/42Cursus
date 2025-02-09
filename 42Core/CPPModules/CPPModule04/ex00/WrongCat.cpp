#include "WrongCat.hpp"

WrongCat::WrongCat( void ) : WrongAnimal("WrongCat") {
	std::cout << "Hello from WrongAnimal constructor" << std::endl;
}

WrongCat& WrongCat::operator=( const WrongCat& rhs ) {
	std::cout << "Hello from WrongCat operator = constructor" << std::endl;
	if (this != &rhs)
		this->type_ = rhs.type_;
	return (*this);
}

WrongCat::WrongCat( const WrongCat& cpy ) {
	std::cout << "Hello from WrongCat cpy constructor" << std::endl;
	*this = cpy;
}

WrongCat::~WrongCat( void ) {
	std::cout << "Hello from WrongCat destructor" << std::endl;
}

void WrongCat::makeSound(void) const {
	std::cout << "vrai miaou" << std::endl;
}
