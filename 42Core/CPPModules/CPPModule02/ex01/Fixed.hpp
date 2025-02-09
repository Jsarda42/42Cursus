#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {

	private:

		int value_;
		static const int nbBits_ = 8;

	public:

		Fixed( void );
		~Fixed( void );
		Fixed( const Fixed& cpy );
		Fixed& operator=( const Fixed& rhs );
		int getRawBits( void ) const;
		void setRawBits( int const raw );
		Fixed( const float floatt );
		Fixed( const int integer );
		float toFloat( void ) const;
		int toInt( void ) const;
};

std::ostream& operator<<(std::ostream& os, const Fixed& rhs);

#endif
