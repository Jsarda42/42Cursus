#include <iostream>
#include "Character.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria *tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);


	std::cout << "\nMY TESTS:\n" << std::endl;
	std::cout << "1.To much materia, not enough space in inventory :" << std::endl;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	std::cout << "\n2.Empty inventory and try to unequip more :" << std::endl;
	me->unequip(0);
	me->unequip(1);
	me->unequip(2);
	me->unequip(3);
	me->unequip(3);
	me->unequip(4);
	me->unequip(-1);

	std::cout << "\n3.Try to use a materia without having it :" << std::endl;
	me->use(0, *bob);
	me->use(1, *bob);
	me->use(2, *bob);
	me->use(3, *bob);
	me->use(4, *bob);
	me->use(-1, *bob);

	Cure *tmp1 = new Cure();
	Cure *tmp2 = new Cure();
	std::cout << "\n4.Try to learn lot of materia :" << std::endl;
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(tmp1);
	src->learnMateria(tmp2);
	std::cout << std::endl;

	delete tmp1;
	delete tmp2;
	delete bob;
	delete me;
	delete src;
	delete tmp;

	return 0;
}
