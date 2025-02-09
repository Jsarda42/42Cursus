#include "Zombie.hpp"

Zombie::Zombie( void ) {
	std::cout << "Creating zombie\n";
}

Zombie::Zombie(std::string name) : _Name (name){
	std::cout << "Creating zombie\n";
}

Zombie::~Zombie(){
	std::cout << "Destroying zombie\n";
}
