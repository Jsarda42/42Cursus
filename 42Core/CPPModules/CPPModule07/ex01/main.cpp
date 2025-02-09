#include "iter.hpp"
#include <iostream>

void cti(int &i) {
	i = i + 1;
}

void cel(std::string& elem) {
	elem = elem + "_modified";
}

void printInt(const int& i) {
	std::cout << i << " ";
}

void printString(const std::string& str) {
	std::cout << str << " ";
}

int main() {
	int arr[] = {1, 2, 3, 4, 5};
	size_t length = sizeof(arr) / sizeof(arr[0]);
	std::string arrs[] = {"hello", "world"};
	size_t lengths = sizeof(arrs) / sizeof(arrs[0]);
	const std::string arrss[] = {"bobo", "bibi"};
	size_t lengthss = sizeof(arrss) / sizeof(arrss[0]);

	iter(arr, length, cti);
	std::cout << "Modified integers: ";
	iter(arr, length, printInt);
	std::cout << std::endl;

	iter(arrs, lengths, cel);
	std::cout << "Modified strings: ";
	iter(arrs, lengths, printString);
	std::cout << std::endl;

	std::cout << "Print const string: ";
	iter(arrss, lengthss, printString);
	std::cout << std::endl;


	return 0;
}
