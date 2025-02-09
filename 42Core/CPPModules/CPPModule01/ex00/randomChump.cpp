#include "Zombie.hpp"

void	Zombie::announce ( void ){
	std::cout << _Name << ": BraiiiiiiinnnzzzZ...\n";
}

void Zombie::randomChump( std::string name ){

	this->_Name = name;
	this->announce();
}
