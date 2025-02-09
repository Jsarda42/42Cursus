#include "Zombie.hpp"

int main(){
	Zombie *zombie;

	zombie = zombieHorde(10, "Froz");

	for (int i = 0; i < 10; i++)
		zombie[i].announce();
	delete [] zombie;
	return (0);
}
