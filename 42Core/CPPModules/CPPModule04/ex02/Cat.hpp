#pragma once
#include "AAnimal.hpp"
#include "Brain.hpp"
#include <iostream>

class Cat : public AAnimal {

	private:

		Brain *brain;

	public:

		Cat( void );
		Cat& operator=( const Cat& rhs );
		Cat( const Cat& cpy );
		~Cat( void );

		std::string getIdeas(int index) const ;
		void setIdeas(std::string idea);
		void makeSound() const;
};
