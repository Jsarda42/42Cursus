#include <iostream>

int main(){
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;

	std::cout << "str adress : " << &str << "\n";
	std::cout << "stringPTR adress : " << stringPTR << "\n";
	std::cout << "stringREF adress : " << &stringREF << "\n";

	std::cout << "str value : " << str << "\n";
	std::cout << "stringPTR value : " << *stringPTR << "\n";
	std::cout << "stringREF value : " << stringREF << "\n";
}

