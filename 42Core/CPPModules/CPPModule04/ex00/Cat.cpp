#include "Cat.hpp"

Cat::Cat( void ) : Animal("Cat") {
	std::cout << "Hello from " << type_ << " constructor" << std::endl;
}

Cat& Cat::operator=( const Cat& rhs ) {
	std::cout << "Hello from " << type_ <<  " operator = constructor" << std::endl;
	if (this != &rhs)
		this->type_ = rhs.type_;
	return (*this);
}

Cat::Cat( const Cat& cpy ) {
	std::cout << "Hello from " << type_ << " cpy constructor" << std::endl;
	*this = cpy;
}

Cat::~Cat( void ) {
	std::cout << "Hello from " << type_ << " destructor" << std::endl;
}

void Cat::makeSound() const {
	std::cout << "miaou" << std::endl;
}
