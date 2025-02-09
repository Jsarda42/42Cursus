#pragma once
#include "Animal.hpp"
#include <iostream>

class Brain {

	private:

		std::string ideas_[100];

	public:

		Brain( void );
		Brain& operator=( const Brain& rhs);
		Brain( const Brain& cpy );
		~Brain( void );
		std::string getIdeas(int index) const;
		void setIdeas(std::string idea);
};
