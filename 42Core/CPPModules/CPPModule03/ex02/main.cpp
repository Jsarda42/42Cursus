#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
	{
		ClapTrap clapTrap("juju");
		clapTrap.attack("Roger");
		clapTrap.beRepaired(10);
		clapTrap.takeDamage(1);
	}
	{
		ScavTrap scavTrap("mark");
		scavTrap.attack("mimi");
		scavTrap.beRepaired(10);
		scavTrap.takeDamage(1);
		scavTrap.guardGate();
	}
	{
		FragTrap fragTrap("toto");
		fragTrap.attack("papa");
		fragTrap.beRepaired(10);
		fragTrap.takeDamage(1);
		fragTrap.highFivesGuys();
	}
	return (0);
}
