#include "Zombie.hpp"

int main(){
	Zombie* zombie;

	zombie = newZombie("hype");
	zombie->announce();
	delete zombie;

	Zombie zombie2;
	zombie2.randomChump("stack");
	return (0);
}
