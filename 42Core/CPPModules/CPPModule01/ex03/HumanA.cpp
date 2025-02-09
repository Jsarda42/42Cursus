#include "HumanA.hpp"

HumanA::~HumanA( void ){
}

HumanA::HumanA(std::string name, Weapon &weapon) : _name(name), _weapon(weapon){
}


void HumanA::attack( void ){
	std::cout << this->_name <<  "attacks with their " << this->_weapon.get_type();
	std::cout << "\n";
}
