#include "ScalarConverter.hpp"
#include "Printer.hpp"

/*********************************	main	   ****************************************/

void ScalarConverter::convert(std::string literal) {
	Type type = getType(literal);

	switch (type) {
		case CHAR: {
			char c = literal[0];
			convertFromChar(c);
			break;
	}
	case INT: {
		int i = std::atoi(literal.c_str());
		convertFromInt(i);
		break;
	}
	case FLOAT: {
		char* end = NULL;
		float f = std::strtof(literal.c_str(), &end);
		if ((*end != '\0' && *end != 'f') || (*end == 'f' && *(end + 1) != '\0')) {
			std::cout << "Invalid or unknown literal.\n";
			break;
		}
		convertFromFloat(f);
		break ;
	}
	case DOUBLE: {
		char* end = NULL;
		double d = std::strtod(literal.c_str(), &end);
		if (*end != '\0') {
			std::cout << "Invalid double literal.\n";
			break;
		}
		convertFromDouble(d);
		break;
	}
	default:
		std::cout << "Invalid or unknown literal.\n";
	}
}

/********************************* identify type ****************************************/

bool ScalarConverter::isCharLiteral(const std::string literal) {
	return literal.size() == 1 && !isdigit(literal[0]);
}

bool ScalarConverter::isIntLiteral(const std::string literal) {
	char* end = NULL;
	long value = std::strtol(literal.c_str(), &end, 10);
	return *end == '\0' && value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max();
}

bool ScalarConverter::isFloatLiteral(const std::string literal) {
	char* end = NULL;
	float value = std::strtof(literal.c_str(), &end);
	return (*end == 'f' || *end == '\0') && !std::isnan(value) && !std::isinf(value);
}

bool ScalarConverter::isDoubleLiteral(const std::string literal) {
	char* end = NULL;
	std::strtod(literal.c_str(), &end);
	return *end == '\0';
}

Type ScalarConverter::getType(const std::string literal) {
	if (isCharLiteral(literal)) return CHAR;
	if (isIntLiteral(literal)) return INT;
	if (isFloatLiteral(literal)) return FLOAT;
	if (isDoubleLiteral(literal)) return DOUBLE;
	return UNKNOWN;
}

/*********************************   convertor   ****************************************/

void ScalarConverter::convertFromChar(char c) {
	if (std::isnan(c)) {
		Printer::printNaN();
		return ;
	}
	Printer::printChar(c);
	Printer::printInt(static_cast<int>(c));
	Printer::printFloat(static_cast<float>(c));
	Printer::printDouble(static_cast<double>(c));
}

void ScalarConverter::convertFromInt(int i) {
	if (std::isnan(i)) {
		Printer::printNaN();
		return ;
	}
	if (i < 32 || i > 126)
		std::cout << "char: Non displayable\n";
	else
		Printer::printChar(static_cast<char>(i));
	Printer::printInt(i);
	Printer::printFloat(static_cast<float>(i));
	Printer::printDouble(static_cast<double>(i));
}

void ScalarConverter::convertFromFloat(float f) {
	if (std::isnan(f)) {
		Printer::printNaN();
		return ;
	}
	if (f < 32 || f > 126)
		std::cout << "char: Non displayable\n";
	else
		Printer::printChar(static_cast<char>(f));
	if (f < std::numeric_limits<int>::min() || f > std::numeric_limits<int>::max())
		Printer::printOverflow();
	else
		Printer::printInt(static_cast<int>(f));
	Printer::printFloat(f);
	Printer::printDouble(static_cast<double>(f));
}

void ScalarConverter::convertFromDouble(double d) {
	if (std::isnan(d)) {
		Printer::printNaN();
		return ;
	}
	if (d < 32 || d > 126)
		std::cout << "char: Non displayable\n";
	else
		Printer::printChar(static_cast<char>(d));
	if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
		Printer::printOverflow();
	else
		Printer::printInt(static_cast<int>(d));
	Printer::printFloat(static_cast<double>(d));
	Printer::printDouble(d);
}
