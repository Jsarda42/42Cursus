#ifndef CONTACT_HPP
# define CONTACT_HPP


#include <iostream>

class Contact {

	private :

		std::string _FirstName;
		std::string _LastName;
		std::string _NickName;
		std::string _PhoneNumber;
		std::string _DarkestSecret;

	public:

		Contact( void );
		~Contact( void );
		void set_first_name(std::string firstName);
		void set_last_name(std::string lastName);
		void set_nickname(std::string nickName);
		void set_phone_number(std::string phoneNumber);
		void set_darkest_secret(std::string darkestSecret);
		std::string get_first_name();
		std::string get_last_name();
		std::string get_nickname();
		std::string get_phone_number();
		std::string get_darkest_secret();
};

#endif
