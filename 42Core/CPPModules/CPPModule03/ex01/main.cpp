#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
	{
		ClapTrap clapTrap("juju");
		clapTrap.attack("Roger");
		clapTrap.beRepaired(10);
		clapTrap.takeDamage(1);
	}
	{
		ScavTrap scavTrap("mark");
		scavTrap.attack("Roger");
		scavTrap.beRepaired(10);
		scavTrap.takeDamage(1);
		scavTrap.guardGate();
	}
	return (0);
}
