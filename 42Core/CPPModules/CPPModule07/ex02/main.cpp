#include "Array.hpp"
#include <iostream>

int main () {
	try {
		Array<int> intArray(5);
		for (int i = 0;i < 5; i++)
	 		intArray[i] = i;
		for (int i = 0;i < 5; i++)
			std::cout << intArray[i] << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Error :" << e.what() << std::endl;
	}

	try {
		Array<std::string> charArray(5);
		charArray[0] = "hello";
		charArray[1] = "world";
		charArray[2] = "this";
		charArray[3] = "is my";
		charArray[4] = "array";

		for (unsigned i = 0;i < charArray.size(); i++)
			std::cout << charArray[i] << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Error :" << e.what() << std::endl;
	}

	try {
		Array<std::string> charArray(5);
		charArray[0] = "hello";
		charArray[1] = "world";
		charArray[2] = "this";
		charArray[3] = "is my";
		charArray[4] = "array";

		Array<std::string> charArrayCpy(charArray.size());
		charArrayCpy = charArray;

		for (unsigned i = 0;i < charArrayCpy.size(); i++)
			std::cout << charArrayCpy[i] << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Error :" << e.what() << std::endl;
	}

	try {
		Array<std::string> charArrayError(5);
		charArrayError[0] = "hello";
		charArrayError[1] = "world";
		charArrayError[2] = "this";
		charArrayError[3] = "is my";
		charArrayError[4] = "array";

		for (unsigned i = 0;i < 7; i++)
			std::cout << charArrayError[i] << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Error :" << e.what() << std::endl;
	}

	return 0;
}
