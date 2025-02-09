#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {

	private:

		int value_;
		static const int nbBits_ = 8;

	public:

		// Constructors
		Fixed( void );
		Fixed( const Fixed& cpy );
		Fixed( const float floatt );
		Fixed( const int integer );

		// Deconstructors
		~Fixed( void );

		// Overloaded Operators
		Fixed& operator=( const Fixed& rhs );

		// Comparison Operators
		bool operator>( const Fixed rhs );
		bool operator<( const Fixed rhs );
		bool operator>=( const Fixed rhs );
		bool operator<=( const Fixed rhs );
		bool operator==( const Fixed rhs );
		bool operator!=( const Fixed rhs );

		// Arithmetic Operators
		float operator+( const Fixed rhs );
		float operator-( const Fixed rhs );
		float operator*( const Fixed rhs );
		float operator/( const Fixed rhs );

		// pre-increment Operators
		Fixed operator++();
		Fixed operator--();
		// post-increment Operators
		Fixed operator--( int );
		Fixed operator++( int );

		// Public Methods
		float toFloat( void ) const;
		int toInt( void ) const;
		static Fixed& min( Fixed& n1, Fixed& n2 );
		static const Fixed& min( const Fixed& n1, const Fixed& n2 );
		static Fixed& max( Fixed& n1, Fixed& n2 );
		static const Fixed& max( const Fixed& n1, const Fixed& n2 );

		// getter
		int getRawBits( void ) const;

		// setter
		void setRawBits( int const raw );
};

std::ostream& operator<<(std::ostream& os, const Fixed& rhs);

#endif
