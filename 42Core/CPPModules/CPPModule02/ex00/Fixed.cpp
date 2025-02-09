#include "Fixed.hpp"

Fixed::Fixed() : value_(0){
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed( const Fixed& cpy ) {
	std::cout << "Copy constructor called" << std::endl;
	*this = cpy;
}

Fixed& Fixed::operator=( const Fixed& rhs ) {
	std::cout << "Copy assignment operator called" << std::endl;
	this->value_ = rhs.value_;
	return (*this);
}

int Fixed::getRawBits( void ) const {
	std::cout << "getRawBits member function called" << std::endl;
	return (value_);
}

void Fixed::setRawBits( int const raw ) {
	value_ = raw;
}
