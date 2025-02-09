#pragma once
#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {

	private:

	public:

		WrongCat( void );
		WrongCat& operator=( const WrongCat& rhs );
		WrongCat( const WrongCat& cpy );
		~WrongCat( void );

		void makeSound() const;
};
