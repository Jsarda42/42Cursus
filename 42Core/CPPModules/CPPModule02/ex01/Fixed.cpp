#include "Fixed.hpp"

Fixed::Fixed() : value_(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed( int integer ) {
	std::cout << "Int constructor called" << std::endl;
	setRawBits(integer << nbBits_);
}

Fixed::Fixed( const float floatt ) {
	std::cout << "Float constructor called" << std::endl;
	setRawBits((int)roundf(floatt * 256));
}

Fixed::Fixed( const Fixed& cpy ) {
	std::cout << "Copy constructor called" << std::endl;
	*this = cpy;
}

Fixed& Fixed::operator=( const Fixed& rhs ) {
	std::cout << "Copy assignment operator called" << std::endl;
	setRawBits(rhs.getRawBits());
	return (*this);
}

std::ostream& operator<<( std::ostream& os, const Fixed& rhs ) {
	os << rhs.toFloat();
	return (os);
}

int Fixed::getRawBits( void ) const {
	return (value_);
}

void Fixed::setRawBits( int const raw ) {
	value_ = raw;
}

float Fixed::toFloat( void ) const {
	float	f;

	f = (float)getRawBits() / (256);
	return (f);
}

int Fixed::toInt( void ) const {
	return (getRawBits() >> nbBits_);
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}
