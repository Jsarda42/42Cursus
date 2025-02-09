#include "Harl.hpp"

int main(int argc, char **argv){
	Harl complain;

	if (argc != 2)
		return (std::cerr << "Wrong number of arguments!\n", 1);
	complain.complain(argv[1]);
	return (0);
}
