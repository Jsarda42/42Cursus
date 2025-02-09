#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

class Weapon{

	private:

		std::string _type;

	public:

		Weapon( std::string weapon);
		~Weapon( void );
		std::string& get_type( void );
		void setType( std::string type );
};

#endif
