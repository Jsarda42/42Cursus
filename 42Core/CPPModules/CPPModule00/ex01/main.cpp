#include "PhoneBook.hpp"

int main()
{
	PhoneBook PhoneBook;
	std::string input;
	int i = 0;

	while (std::cin.eof() != 1)
	{
		std::cout << "Please enter a command : ADD , SEARCH , EXIT ! ";
		std::cin >> input;
		if (input == "ADD")
			i = PhoneBook.add_contact(i);
		if (input == "SEARCH")
		{
			PhoneBook.print_contact();
		}
		if (input == "EXIT")
			break ;
	}
	return (0);
}
