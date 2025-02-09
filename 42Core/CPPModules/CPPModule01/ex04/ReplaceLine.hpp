#ifndef CHECKLINE_HPP
#define CHECKLINE_HPP

#include <iostream>
#include <fstream>
#include<list>

class ReplaceLine{

	private:

		std::string _Line;

	public:

		ReplaceLine( void );
		~ReplaceLine( void );
		std::string replaceLine( std::string line, std::string s1 , std::string s2);
};

#endif
