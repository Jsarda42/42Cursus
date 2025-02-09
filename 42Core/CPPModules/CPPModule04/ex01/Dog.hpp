#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {

	private:

		Brain *brain;

	public:

		Dog( void );
		Dog& operator=( const Dog& rhs );
		Dog( const Dog& cpy );
		~Dog( void );

		void makeSound() const;
		std::string getIdeas(int index) const ;
		void setIdeas(std::string idea);
};
