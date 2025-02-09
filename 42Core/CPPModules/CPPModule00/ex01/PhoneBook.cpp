#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{

};

PhoneBook::~PhoneBook()
{

};

int PhoneBook::add_contact(int index)
{
	std::string FirstName;
	std::string LastName;
	std::string PhoneNumber;
	std::string DarkestSecret;
	std::string NickName;

	std::cout << "Please enter your first name : ";
	std::cin >> FirstName;
	std::cout << "Please enter your last name : ";
	std::cin >> LastName;
	std::cout << "Please enter your phone number : ";
	std::cin >> PhoneNumber;
	std::cout << "Please enter your nickname : ";
	std::cin >> NickName;
	std::cout << "Please enter your darkest secret : ";
	std::cin >> DarkestSecret;

	std::cout << "YOUR INDEX: " << index << "\n";
	if (index > 7)
		index = 0;
	this->_contacts[index].set_first_name(FirstName);
	this->_contacts[index].set_last_name(LastName);
	this->_contacts[index].set_nickname(NickName);
	this->_contacts[index].set_darkest_secret(DarkestSecret);
	this->_contacts[index].set_phone_number(PhoneNumber);
	return (index + 1);
}


std::string	resize_str(std::string str)
{
	if (str.size() > 10)
	{
		str.resize(9);
		str += ".";
	}
	return (str);
}

std::string empty_space(int size)
{
	std::string str = "";
	for (int i = 0; i < size; i++)
		str += " ";
	return (str);
}

void PhoneBook::print_contact()
{
	Contact contact;
	std::string index;
	int id = 0;

	std::cout << " ___________________________________________  \n";
	std::cout << "|     Index|  FirstNa.|  LastName|  Nickname|\n";
	std::cout << "|-------------------------------------------|\n";
	for(int i = 0; i < 8 && !(_contacts[i].get_first_name().empty()); i++){
		std::cout << "|" << empty_space(9) << i << "|";
		std::cout << empty_space(10 - resize_str(_contacts[i].get_first_name()).size()) << resize_str(_contacts[i].get_first_name()) << "|";
		std::cout << empty_space(10 -resize_str(_contacts[i].get_last_name()).size()) << resize_str(_contacts[i].get_last_name()) << "|";
		std::cout << empty_space(10 - resize_str(_contacts[i].get_nickname()).size()) << resize_str(_contacts[i].get_nickname()) << "|\n";
		std::cout << "|-------------------------------------------|\n";
	}
	std::cout << "|___________________________________________|\n";
	std::cout << "Please enter the id of the contact ";
	std::cin >> index;
	if (!(std::isdigit(index[0])))
	{
		std::cout << "Wrong index format\n";
		return ;
	}
	id = std::atoi(index.c_str());
	if (id < 0 || id > 7) {
		std::cout << "Enter index from 0 to 7\n";
		return ;
	}
	else if (_contacts[id].get_first_name().empty()) {
		std::cout << "This contact does not exist\n";
		return ;
	}
	std::cout << " _________________________________________________________________  \n";
	std::cout << "|     Index|FirstName|  LastName|  Nickname|Phone_numb.|Darkest s.|\n";
	std::cout << "|-----------------------------------------------------------------|\n";
	std::cout << "|" << empty_space(9) << id << "|";
	std::cout << empty_space(10 - resize_str(_contacts[id].get_first_name()).size()) << resize_str(_contacts[id].get_first_name()) << "|";
	std::cout << empty_space(10 - resize_str(_contacts[id].get_last_name()).size()) << resize_str(_contacts[id].get_last_name()) << "|";
	std::cout << empty_space(10 - resize_str(_contacts[id].get_nickname()).size()) << resize_str(_contacts[id].get_nickname()) << "|";
	std::cout << empty_space(10 - resize_str(_contacts[id].get_phone_number()).size()) << resize_str(_contacts[id].get_phone_number()) << "|";
	std::cout << empty_space(10 - resize_str(_contacts[id].get_darkest_secret()).size()) << resize_str(_contacts[id].get_darkest_secret()) << "|\n";
	std::cout << "|_________________________________________________________________|\n";
}
