#include "FragTrap.hpp"

FragTrap::FragTrap( void ) : ClapTrap("default") {
	HitPoints_ = 100;
	EnergyPoints_ = 50;
	AttackDamage_ = 20;
	std::cout << "FragTrap Default constructor called" << std::endl;
}

FragTrap::FragTrap( std::string name ) : ClapTrap(name) {
	HitPoints_ = 100;
	EnergyPoints_ = 100;
	AttackDamage_ = 30;
	std::cout << "FragTrap constructor called (with param)" << std::endl;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap destructor called" << std::endl;
}

FragTrap& FragTrap::operator=( FragTrap& rhs ) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		this->name_ = rhs.name_;
		this->HitPoints_ = rhs.HitPoints_;
		this->EnergyPoints_ = rhs.EnergyPoints_;
		this->AttackDamage_ = rhs.AttackDamage_;
	}
	return (*this);
}

FragTrap::FragTrap( FragTrap& cpy ) {
	*this = cpy;
}

void FragTrap::attack( const std::string& target ) {
	if (EnergyPoints_ == 0) {
		std::cout << "FragTrap " << name_ << " does not have enough energy " << std::endl;
		return ;
	}
	std::cout << "FragTrap " << name_ << " attacks " << target << " , causing " << AttackDamage_ << " points of damage!" << std::endl;
	EnergyPoints_--;
}

void FragTrap::highFivesGuys(void) {
	std::cout << "High Fives from FragTrap!" << std::endl;
}
