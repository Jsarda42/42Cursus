#include "Fixed.hpp"

Fixed::Fixed() : value_(0) {
	//std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed( int integer ) {
	//std::cout << "Int constructor called" << std::endl;
	setRawBits(integer << nbBits_);
}

Fixed::Fixed( const float floatt ) {
	//std::cout << "Float constructor called" << std::endl;
	setRawBits((int)roundf(floatt * 256));
}

Fixed::Fixed( const Fixed& cpy ) {
	//std::cout << "Copy constructor called" << std::endl;
	*this = cpy;
}

int Fixed::getRawBits( void ) const {
	return (value_);
}

void Fixed::setRawBits( int const raw ) {
	value_ = raw;
}

float Fixed::toFloat( void ) const {
	return (float)getRawBits() / (256);
}

int Fixed::toInt( void ) const {
	return (getRawBits() >> nbBits_);
}

Fixed::~Fixed() {
	//std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=( const Fixed& rhs ) {
	//std::cout << "Copy assignment operator called" << std::endl;
	setRawBits(rhs.getRawBits());
	return (*this);
}

std::ostream& operator<<( std::ostream& os, const Fixed& rhs ) {
	os << rhs.toFloat();
	return (os);
}

Fixed& Fixed::max( Fixed& n1, Fixed& n2 ) {
	if (n1.toFloat() > n2.toFloat())
		return (n1);
	return (n2);
}

const Fixed& Fixed::max( const Fixed& n1, const Fixed& n2 ) {
	if (n1.toFloat() > n2.toFloat())
		return (n1);
	return (n2);
}

Fixed& Fixed::min( Fixed& n1, Fixed& n2 ) {
	if (n1.toFloat() > n2.toFloat())
		return (n2);
	return (n1);
}

const Fixed& Fixed::min( const Fixed& n1, const Fixed& n2 ) {
	if (n1.toFloat() > n2.toFloat())
		return (n2);
	return (n1);
}

float Fixed::operator+( const Fixed rhs ) {
	return (this->toFloat() + rhs.toFloat());
}

float Fixed::operator-( const Fixed rhs ) {
	return (this->toFloat() - rhs.toFloat());
}

float Fixed::operator*( const Fixed rhs ) {
	return (this->toFloat() * rhs.toFloat());
}

float Fixed::operator/( const Fixed rhs ) {
	return (this->toFloat() / rhs.toFloat());
}

bool Fixed::operator>( const Fixed rhs ) {
	return (this->toFloat() > rhs.toFloat());
}

bool Fixed::operator<( const Fixed rhs ) {
	return (this->toFloat() < rhs.toFloat());
}

bool Fixed::operator>=( const Fixed rhs ) {
	return (this->toFloat() >= rhs.toFloat());
}

bool Fixed::operator<=( const Fixed rhs ) {
	return (this->toFloat() <= rhs.toFloat());
}

bool Fixed::operator==( const Fixed rhs ) {
	return (this->toFloat() == rhs.toFloat());
}

bool Fixed::operator!=( const Fixed rhs ) {
	return (this->toFloat() != rhs.toFloat());
}

Fixed Fixed::operator++() {
	value_++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed tmp = *this;
	++this->value_;
	return (tmp);
}

Fixed Fixed::operator--() {
	value_--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed tmp = *this;
	--this->value_;
	return (tmp);
}

