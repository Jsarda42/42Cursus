#include "ClapTrap.hpp"

int main() {
	ClapTrap clapTrap("juju");
	ClapTrap clapTrap2;
	ClapTrap clapTrap3(clapTrap);

	clapTrap2 = clapTrap;

	clapTrap.attack("Roger");
	clapTrap.beRepaired(10);
	clapTrap.takeDamage(1);
	clapTrap2.attack("test");
}
