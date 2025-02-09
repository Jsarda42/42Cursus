#include "ClapTrap.hpp"

ClapTrap::ClapTrap( void ) : name_("default"), HitPoints_(10), EnergyPoints_(0), AttackDamage_(0) {
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap( std::string name ) : name_(name), HitPoints_(10), EnergyPoints_(0), AttackDamage_(0) {
	std::cout << "Constructor called (with param)" << std::endl;
}

ClapTrap::~ClapTrap() {
	std::cout << "Destructor called" << std::endl;
}

ClapTrap::ClapTrap( const ClapTrap& cpy ) {
	std::cout << "Copy constructor called" << std::endl;
	*this = cpy;
}

ClapTrap& ClapTrap::operator=( const ClapTrap& rhs) {
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

void ClapTrap::attack( const std::string& target ) {
	if (EnergyPoints_ == 0) {
		std::cout << "ClapTrap " << name_ << " does not have enough energy " << std::endl;
		return ;
	}
	std::cout << "ClapTrap " << name_ << " attacks " << target << " , causing " << AttackDamage_ << " points of damage!" << std::endl;
	EnergyPoints_--;
}

void ClapTrap::takeDamage(unsigned int amount) {
	std::cout << "ClapTrap " << name_ << " takes " << amount << " points of damage!" << std::endl;
	HitPoints_ -= amount;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (EnergyPoints_ == 0) {
		std::cout << "ClapTrap " << name_ << " does not have enough energy " << std::endl;
		return ;
	}
	std::cout << "ClapTrap " << name_ << " repairs " << amount << " points of life!" << std::endl;
	HitPoints_ += amount;
	EnergyPoints_--;
}
