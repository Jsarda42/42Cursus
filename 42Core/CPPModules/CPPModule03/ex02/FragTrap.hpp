#pragma once
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {

	private:


	public:

		FragTrap& operator=( FragTrap& rhs );
		FragTrap( FragTrap& cpy );
		FragTrap( void );
		FragTrap( std::string name );
		~FragTrap( void );
		
		void attack( const std::string& target );
		void highFivesGuys( void );
};
