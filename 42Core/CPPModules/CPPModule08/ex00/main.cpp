#include "easyfind.hpp"
#include <vector>
#include <list>

int main () {
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	try {
		std::cout << easyfind(v, 3) << std::endl;
		std::cout << easyfind(v, 6) << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Value not found" << std::endl;
	}

	std::list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	try {
		std::cout << easyfind(l, 2) << std::endl;
		std::cout << easyfind(l, 8) << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Value not found" << std::endl;
	}
	return 0;
}
