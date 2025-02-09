#pragma once
#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {

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
