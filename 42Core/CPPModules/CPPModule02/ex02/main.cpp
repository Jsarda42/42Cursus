#include "Fixed.hpp"

int main( void ) {
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << "initial value for a : " << a << std::endl;
	std::cout << "pre incrementation : " << ++a << std::endl;
	std::cout << "new value for a :" << a << std::endl;
	std::cout << "pre decrementation : " << --a << std::endl;
	std::cout << "new value for a :" << a << std::endl;
	std::cout << "post incrementation : " << a++ << std::endl;
	std::cout << "new value for a :" << a << std::endl;
	std::cout << "post decrementation : " << a-- << std::endl;
	std::cout << "new value for a :" << a << std::endl;
	std::cout << "intial value for b :"<< b << std::endl;
	std::cout << "the max is : " << Fixed::max( a, b ) << std::endl;
	std::cout << "the min is : " << Fixed::min( a, b ) << std::endl;
	if (a > b)
		std::cout << "a is bigger than b" << std::endl;
	if (a < b)
		std::cout << "a is smaller than b" << std::endl;
	return 0;
}
