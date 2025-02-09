#pragma once
#include "Animal.hpp"

class Cat : public Animal {

	private:

	public:

		Cat( void );
		Cat& operator=( const Cat& rhs );
		Cat( const Cat& cpy );
		~Cat( void );

		void makeSound() const;
};
