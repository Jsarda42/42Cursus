#include "RPN.hpp"
#include "iostream"
#include "RPN.hpp"

int main (int argc, char **argv) {
	try {
		if (argc != 2)
			throw std::runtime_error("Wrong number of arguments");
		RPN expression;
		expression.evaluateExpression(argv[1]);
	}
	catch (std::exception &e) {
		std::cerr << "Error : " << e.what() << "\n";
		return 1;
	}
}
