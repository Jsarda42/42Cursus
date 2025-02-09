#pragma once
#include "Animal.hpp"

class Dog : public Animal {

	private:

	public:

		Dog( void );
		Dog& operator=( const Dog& rhs );
		Dog( const Dog& cpy );
		~Dog( void );

		void makeSound() const;
};
