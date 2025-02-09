#include "HumanB.hpp"

HumanB::HumanB(std::string name){
	_name = name;
}

HumanB::~HumanB( void ){
}

void HumanB::attack( void ){
	std::cout << _name <<  "attacks with their " << _weapon->get_type();
	std::cout << "\n";
}

void HumanB::setWeapon( Weapon &weapon){
	_weapon = &weapon;
}
