#pragma once

#include <iostream>

class AAnimal {

	protected:

		std::string type_;

	public:

		AAnimal( void );
		AAnimal(std::string type);
		AAnimal& operator=( const AAnimal& rhs);
		AAnimal( const AAnimal& cpy );
		virtual ~AAnimal( void ) = 0;

		virtual std::string getType( void ) const;
		virtual void makeSound() const = 0;
};
