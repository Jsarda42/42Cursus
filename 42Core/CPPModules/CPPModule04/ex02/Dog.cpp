#include "Dog.hpp"

Dog::Dog( void ) : AAnimal("Dog") {
	std::cout << "Hello from " << type_ << " constructor" << std::endl;
	brain = new Brain();
}

Dog& Dog::operator=( const Dog& rhs ) {
	std::cout << "Hello from " << type_ <<  " operator = constructor" << std::endl;
	if (this != &rhs) {
		type_ = rhs.type_;
		delete brain;
		brain = new Brain(*rhs.brain);
	}
	return (*this);
}

Dog::Dog( const Dog& cpy ) {
	std::cout << "Hello from " << type_ << " cpy constructor" << std::endl;
	type_ = cpy.type_;
	brain = new Brain(*cpy.brain);
	*this = cpy;
}

Dog::~Dog( void ) {
	delete brain;
	std::cout << "Hello from " << type_ << " destructor" << std::endl;
}

void Dog::makeSound() const {
	std::cout << "miaou" << std::endl;
}

std::string Dog::getIdeas(int index) const {
	return (brain->getIdeas(index));
}

void Dog::setIdeas(std::string idea) {
	brain->setIdeas(idea);
}


