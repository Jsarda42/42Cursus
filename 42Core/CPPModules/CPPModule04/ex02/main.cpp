#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int	main(void)
{
	const AAnimal *(animals[10]);
	for (int i = 0; i < 10; i++) {
		if (i < 5)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}

	for (int i = 0; i < 5; i++) {
			delete animals[i];
	}
	return (0);
}
