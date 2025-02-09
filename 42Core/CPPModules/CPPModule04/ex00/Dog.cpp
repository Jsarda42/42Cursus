#include "Dog.hpp"

Dog::Dog( void ) : Animal("Dog") {
	std::cout << "Hello from " << type_ << " constructor" << std::endl;
}

Dog& Dog::operator=( const Dog& rhs ) {
	std::cout << "Hello from " << type_ << " operator = constructor" << std::endl;
	if (this != &rhs)
		this->type_ = rhs.type_;
	return (*this);
}

Dog::Dog( const Dog& cpy ) {
	std::cout << "Hello from " << type_ << " cpy constructor" << std::endl;
	*this = cpy;
}

Dog::~Dog( void ) {
	std::cout << "Hello from " << type_ << " destructor" << std::endl;
}
void Dog::makeSound() const {
	std::cout << "woof" << std::endl;
}


