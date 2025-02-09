#include "Contact.hpp"

Contact::Contact(void)
{
}

Contact::~Contact(void)
{
}

void Contact::set_first_name(std::string firstName)
{
	_FirstName = firstName;
}

void Contact::set_last_name(std::string lastName)
{
	_LastName = lastName;
}

void Contact::set_nickname(std::string nickName)
{
	_NickName = nickName;
}

void Contact::set_phone_number(std::string phoneNumber)
{
	_PhoneNumber = phoneNumber;
}

void Contact::set_darkest_secret(std::string darkestSecret)
{
	_DarkestSecret = darkestSecret;
}

std::string Contact::get_first_name()
{
	return (this->_FirstName);
}


std::string Contact::get_last_name()
{
	return (this->_LastName);
}


std::string Contact::get_phone_number()
{
	return (this->_PhoneNumber);
}


std::string Contact::get_darkest_secret()
{
	return (this->_DarkestSecret);
}


std::string Contact::get_nickname()
{
	return (this->_NickName);
}
