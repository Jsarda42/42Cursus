#include "Base.hpp"
#include<cstdlib>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "iostream"
#include <ctime>

Base *generate(void) {
	int random = (std::rand() % 3) + 1;
	switch (random) {
	case 1:
		return new A;
		break;
	case 2:
		return new B;
		break;
	case 3:
		return new C;
		break;
	}
	return NULL;
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return ;
	}
	catch(const std::exception& e) {}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return ;
	}
	catch(const std::exception& e) {}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return ;
	}
	catch(const std::exception& e) {}
}

int main() {
	std::srand(std::time(0));
	Base *randomP = generate();
	Base &randomRef = *randomP;
	std::cout << "***identify pointer***" << std::endl;
	identify(randomP);
	std::cout << "*****identify ref*****" << std::endl;
	identify(randomRef);
	delete randomP;
}
