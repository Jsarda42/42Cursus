#pragma once
#include <iostream>

class ClapTrap {

	private:

		std::string name_;
		int	HitPoints_;
		int	EnergyPoints_;
		int	AttackDamage_;

	public:

		ClapTrap( void );
		ClapTrap( std::string name_ );
		ClapTrap( const ClapTrap& cpy );
		ClapTrap& operator=( const ClapTrap& );
		~ClapTrap();
		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};
