#include "Cat.hpp"

Cat::Cat( void ) : AAnimal("cat") {
	std::cout << "Hello from " << type_ << " constructor" << std::endl;
	brain = new Brain();
}

Cat& Cat::operator=( const Cat& rhs ) {
	std::cout << "Hello from " << type_ <<  " operator = constructor" << std::endl;
	if (this != &rhs) {
		type_ = rhs.type_;
		delete brain;
		brain = new Brain(*rhs.brain);
	}
	return (*this);
}

Cat::Cat( const Cat& cpy ) {
	std::cout << "Hello from " << type_ << " cpy constructor" << std::endl;
	type_ = cpy.type_;
	brain = new Brain(*cpy.brain);
	*this = cpy;
}

Cat::~Cat( void ) {
	delete brain;
	std::cout << "Hello from " << type_ << " destructor" << std::endl;
}

void Cat::makeSound() const {
	std::cout << "miaou" << std::endl;
}

std::string Cat::getIdeas(int index) const {
	return (brain->getIdeas(index));
}

void Cat::setIdeas(std::string idea) {
	brain->setIdeas(idea);
}
