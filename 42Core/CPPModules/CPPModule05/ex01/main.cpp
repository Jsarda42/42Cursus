#include "Bureaucrat.hpp"
#include "Form.hpp"

void	sectionTitle(const std::string& title) {
	std::cout	<< std::endl
				<< "*** " << title << " ***"
				<< std::endl << std::endl;
}

void	printError(std::exception& e) {
	std::cout << "Error: " << e.what() << std::endl;
}

int	main() {
	Bureaucrat	burro("burro", 42);
	std::cout << burro;

	sectionTitle("constructor");
	try {
		Form	formaccio("formaccio", 1000, 1);
	}
	catch (std::exception& e) {
		printError(e);
	}

	try {
		Form	formaccio("formaccio", 42, 0);
	}
	catch (std::exception& e) {
		printError(e);
	}

	try {
		Form	formino("formino", 42, 42);
		Form	formone("formone", 1, 1);

		std::cout << std::endl << formino << formone;

		sectionTitle("sign twice");
		burro.signForm(formino);
		std::cout << formino;
		burro.signForm(formino);

		sectionTitle("grade too low");
		burro.signForm(formone);
	}
	catch (std::exception& e) {
		printError(e);
	}
}
