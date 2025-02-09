#pragma once
#include <iostream>

class Animal {

	protected:

		std::string type_;

	public:

		Animal( void );
		Animal(std::string type);
		Animal& operator=( const Animal& rhs);
		Animal( const Animal& cpy );
		virtual ~Animal( void );

		std::string getType( void ) const ;
		virtual void makeSound() const;
};
