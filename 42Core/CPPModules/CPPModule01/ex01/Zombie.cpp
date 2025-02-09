#include "Zombie.hpp"

Zombie::Zombie( void ){
	std::cout << "Creating zombie\n";
}

Zombie::Zombie( std::string name) : _Name (name){
	
}

Zombie::~Zombie(){
	std::cout << "Destroying zombie\n";
}

void	Zombie::announce( void ){
	std::cout << _Name << ": BraiiiiiiinnnzzzZ...\n";
}

void Zombie::setName( std::string name){
	_Name = name;
}