#include "Printer.hpp"

void	Printer::printChar(const char c) {
	if (std::isprint(c))
		std::cout << "char: '" << static_cast<char>(c) << "'\n";
	else
		std::cout << "char: Non displayable\n";
}

void	Printer::printInt(const int i) {
	if (i < std::numeric_limits<int>::min()
		|| i > std::numeric_limits<int>::max())
		std::cout << "int: Overflow\n";
	else
		std::cout << "int: " << i << "\n";
}

void	Printer::printFloat(const float f) {
	std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f\n";
}

void	Printer::printDouble(const double d) {
	std::cout << "double: " << std::fixed << std::setprecision(1) << d << "\n";
}

void Printer::printNaN(void) {
	std::cout << "char: impossible\n";
	std::cout << "int: impossible\n";
	std::cout << "float: nanf\n";
	std::cout << "double: nan\n";
}

void Printer::printOverflow(void) {
	std::cout << "int: overflow\n";
}
