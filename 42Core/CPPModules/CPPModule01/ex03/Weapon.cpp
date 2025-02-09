#include "Weapon.hpp"

Weapon::Weapon( std::string type) : _type(type){
}

Weapon::~Weapon( void ){
}

std::string& Weapon::get_type( void ){
	return (_type);
}

void Weapon::setType( std::string type ){
	_type = type;
}
