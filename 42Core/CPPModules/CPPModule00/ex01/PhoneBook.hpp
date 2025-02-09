#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include "Contact.hpp"
#include <stdlib.h>

class PhoneBook {
	private :

		Contact _contacts[8];

	public :

		PhoneBook();
		~PhoneBook();
		int add_contact(int index);
		void print_contact();
};

#endif
