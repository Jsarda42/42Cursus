#include "ScavTrap.hpp"

ScavTrap::ScavTrap( void ) : ClapTrap("default") {
	HitPoints_ = 100;
	EnergyPoints_ = 50;
	AttackDamage_ = 20;
	std::cout << "ScavTrap Default constructor called" << std::endl;
}

ScavTrap::ScavTrap( std::string name ) : ClapTrap(name) {
	HitPoints_ = 100;
	EnergyPoints_ = 50;
	AttackDamage_ = 20;
	std::cout << "ScavTrap constructor called (with param)" << std::endl;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap destructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=( ScavTrap& rhs ) {
	if (this != &rhs)
	{
		this->name_ = rhs.name_;
		this->HitPoints_ = rhs.HitPoints_;
		this->EnergyPoints_ = rhs.EnergyPoints_;
		this->AttackDamage_ = rhs.AttackDamage_;
	}
	return (*this);
}

ScavTrap::ScavTrap( ScavTrap& cpy ) {
	*this = cpy;
}

void ScavTrap::attack( const std::string& target ) {
	if (EnergyPoints_ == 0) {
		std::cout << "ScavTrap " << name_ << " does not have enough energy " << std::endl;
		return ;
	}
	std::cout << "ScavTrap " << name_ << " attacks " << target << " , causing " << AttackDamage_ << " points of damage!" << std::endl;
	EnergyPoints_--;
}

void ScavTrap::guardGate() {
	std::cout << "ScavTrap " << name_ << " is now in gate keeper mode" << std::endl;
}
