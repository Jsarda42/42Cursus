#ifndef FIXED_HPP
#define FIXED_HPP


#include <iostream>

class Fixed {

	private:

		int value_;
		static const int nbBits_ = 8;

	public:

		Fixed( void );
		Fixed( const Fixed& cpy );
		Fixed& operator=( const Fixed& rhs );
		~Fixed( void );
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};

#endif
