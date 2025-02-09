
#define RED        "\033[0;31m"
#define GREEN    "\033[0;32m"
#define YELLOW    "\033[0;33m"
#define ORANGE "\033[38;5;208m"
#define BLUE    "\033[0;34m"
#define MAGENTA    "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE    "\033[0;37m"
#define BOLD       "\033[1m"
#define UNDERLINE  "\033[4m"
#define ITALIC     "\033[3m"
#define RESET      "\033[0m"

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{
	{
		std::cout << GREEN << "---------------------------------------------------" RESET << std::endl;
		std::cout << GREEN <<"TESTING DEEP COPY WITH ASSIGNMENT OPERATOR:" << std::endl;
		std::cout << "---------------------------------------------------" RESET << std::endl;
		Cat basic;
		basic.setIdeas("I am a cute cat");
		std::cout << RED << BOLD << basic.getIdeas(0) << RESET << std::endl;
		std::cout << std::endl;
		{
			Cat still_basic = basic;
			std::cout << RED << BOLD << still_basic.getIdeas(0) << RESET << std::endl;
			std::cout << std::endl;
		}
		std::cout << RED << BOLD << basic.getIdeas(0) << RESET << std::endl;
		std::cout << std::endl;
	}
	std::cout << GREEN << "---------------------------------------------------" RESET << std::endl;
	return 0;
}
