#pragma once
#include "Animal.hpp"

class WrongAnimal {

	private:

	protected:

		std::string type_;

	public:

		WrongAnimal( void );
		WrongAnimal(std::string type);
		WrongAnimal& operator=( const WrongAnimal& rhs);
		WrongAnimal( const WrongAnimal& cpy );
		virtual ~WrongAnimal( void );

		std::string getType( void ) const ;
		void makeSound() const;
};
