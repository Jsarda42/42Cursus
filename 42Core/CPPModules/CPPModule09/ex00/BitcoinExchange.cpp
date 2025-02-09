#include "BitcoinExchange.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& cpy) {
	data_ = cpy.data_;
	date_ = cpy.date_;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
	if (this != &rhs) {
		data_ = rhs.data_;
		date_ = rhs.date_;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {}

void BitcoinExchange::initData(void) {
	std::ifstream file("data.csv");
	if (!file.is_open()) {
		std::cerr << "Error: Could not open data file " << "data.csv" << "\n";
		return ;
	}
	std::string line;
	std::string date;
	std::string value;
	double priceValue = 0;
	std::getline(file, line);
	if (line != "date,exchange_rate") {
		std::cerr << "Error: Wrong header format. Expected 'date,exchange_rate'." << "\n";
		return;
	}
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		if (std::getline(ss, date, ',') && std::getline(ss, value) ) {
			try {
				for (unsigned int i = 0; i < value.size();i++) {
					if (value[i] != '.' && !std::isdigit(value[i])) {
						std:: cout << value[i]<< std::endl;
						std::cerr << "Wrong value: only numeric values are accepted ." << "\n";
						return;
					}
				}
				priceValue = std::atof(value.c_str());
				if (priceValue < 0)
					std::cerr << "Wrong value: only non-negative value accepted'.";
				parseDate(date);
				data_[date] = priceValue;
			}
			catch (const std::exception &e){
				std::cerr << "Error: " << e.what() << "\n";
				return ;
			}
		}
	}
}

bool BitcoinExchange::parseLine(std::string line) {
	std::string date;
	std::string value;
	std::istringstream ss(line);
	if (std::getline(ss, date, '|') && std::getline(ss, value)) {
		if (date[date.size() - 1] == ' ') {
			date = date.substr(0, date.size() - 1);
		}
		// check the maxint
		if (value.size() > 10) {
			std::cerr << "Error: too large a number" << "\n";
			return false;
		}
		if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
			std::cerr << "Error: Invalid date format for '" << date << "'! Expected format: YYYY-MM-DD" << "\n";
			return false;
		}
		if (value[0] == ' ') {
			value = value.substr(1, value.size() - 1);
		}
		if (value.size() == 0) {
			std::cerr << "Error: Invalid value format for '" << value << "'! Expected a number" << "\n";
			return false;
		}
		double priceValue = std::atof(value.c_str());
		if (priceValue < 0) {
			std::cerr << "Error: not a positive number." << "\n";
			return false;
		}
		parseLineDate(date);
	}
	else {
		std::cerr << "Error: bad input => " << date  << "\n";
		return false;
	}
	return true;
}

void BitcoinExchange::processData(std::string inputFile) {
	std::string value;
	std::string date;

	std::ifstream file(inputFile.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: Could not open input file " << inputFile << "\n";
		return ;
	}
	std::string line;
	std::getline(file, line);
	if (line != "date | value") {
		std::cerr << "Error: Wrong header format. Expected 'date | value'." << "\n";
		return ;
	}
	while (std::getline(file, line)) {
		if (parseLine(line)) {
			std::istringstream ss(line);
			std::getline(ss, date, '|') ;
			std::getline(ss, value);
			std::map<std::string, double>::iterator it = data_.upper_bound(date);
			if (it != data_.begin()) {
				--it;
			}
			std::cout << date << " => " << value << " = " << (it->second * std::atof(value.c_str())) << "\n";
		}
	}
}

void BitcoinExchange::parseLineDate(std::string date) {
	if (date[4] != '-' || date[7] != '-' || date.size() != 10) {
		std::cerr << "Invalid date format for '" + date + "'! Expected format: YYYY-MM-DD\n";
		return ;
	}
	date_["year"] = date.substr(0, 4).c_str();
	date_["month"] = date.substr(5, 2).c_str();
	date_["day"] = date.substr(8, 2).c_str();

	int year = std::atoi(date_["year"].c_str());
	int month = std::atoi(date_["month"].c_str());
	int day = std::atoi(date_["day"].c_str());

	for (unsigned int i = 0; i < date_["year"].size(); i++) {
		if (!std::isdigit(date_["year"][i])) {
			std::cerr << "Invalid year format for '" + date + "'! Only numbers accepted\n";
			return ;
		}
	}
	for (unsigned int i = 0; i < date_["month"].size(); i++) {
		if (!std::isdigit(date_["month"][i])) {
			std::cerr << "Invalid month format for '" + date + "'! Only numbers accepted\n";
		 return ;
		}
	}
	for (unsigned int i = 0; i < date_["day"].size(); i++) {
		if (!std::isdigit(date_["day"][i])) {
			std::cerr << "Invalid day format for '" + date + "' Only numbers accepted\n";
			return ;
		}
	}

	std::time_t t = std::time(0);
	std::tm* localTime = std::localtime(&t);
	int currentYear = localTime->tm_year + 1900;

	std::ostringstream oss;
	oss << currentYear;
	if (year < 2009 || year > currentYear) {
		std::cerr << "Invalid year format for '" + date + "' the year should be between 2009 and " + oss.str() << "\n";
		return ;
	}

	std::ostringstream ss;
	ss << month;

	if (month < 1 || month > 12) {
		std::cerr << "Invalid month format for '" + date + "' there is only 12 month a year\n";
		return ;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30 || day < 1) {
			std::cerr << "Invalid day format for '" + date + "' month is 30 days\n";
			return ;
		}
	}
	else if (month != 2) {
		if (day > 31 || day < 1) {
			std::cerr << "Invalid day format for '" + date + "' month is 31 days\n";
			return ;
		}
	}
	else {
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
			if (day < 1 || day > 29) {
				std::cerr << "Invalid day format for '" + date + "' February has 29 days in a leap year\n";
				return ;
			}
		}
		else if (day < 1 || day > 28) {
			std::cerr << "Invalid day format for '" + date + "' February has 28 days in a common year\n";
			return ;
		}
	}
}

void BitcoinExchange::parseDate(std::string date) {
	if (date[4] != '-' || date[7] != '-' || date.size() != 10)
		throw WrongDateFormatException("Invalid date format for '" + date + "'! Expected format: YYYY-MM-DD");
	date_["year"] = date.substr(0, 4).c_str();
	date_["month"] = date.substr(5, 2).c_str();
	date_["day"] = date.substr(8, 2).c_str();

	int year = std::atoi(date_["year"].c_str());
	int month = std::atoi(date_["month"].c_str());
	int day = std::atoi(date_["day"].c_str());

	for (unsigned int i = 0; i < date_["year"].size(); i++) {
		if (!std::isdigit(date_["year"][i]))
			throw WrongDateFormatException("Invalid year format for '" + date + "'! Only numbers accepted");
	}
	for (unsigned int i = 0; i < date_["month"].size(); i++) {
		if (!std::isdigit(date_["month"][i]))
			throw WrongDateFormatException("Invalid month format for '" + date + "'! Only numbers accepted");
	}
	for (unsigned int i = 0; i < date_["day"].size(); i++) {
		if (!std::isdigit(date_["day"][i]))
			throw WrongDateFormatException("Invalid day format for '" + date + "' Only numbers accepted");
	}

	std::time_t t = std::time(0);
	std::tm* localTime = std::localtime(&t);
	int currentYear = localTime->tm_year + 1900;

	std::ostringstream oss;
	oss << currentYear;
	if (year < 2009 || year > currentYear)
		throw WrongDateFormatException("Invalid year format for '" + date + "' the year should be between 2009 and " + oss.str());

	std::ostringstream ss;
	ss << month;

	if (month < 1 || month > 12)
		throw WrongDateFormatException("Invalid month format for '" + date + "' there is only 12 month a year");
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30 || day < 1)
			throw WrongDateFormatException("Invalid day format for '" + date + "' month is 30 days");
	}
	else if (month != 2) {
		if (day > 31 || day < 1)
			throw WrongDateFormatException("Invalid day format for '" + date + "' month is 31 days");
	}
	else {
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
			if (day < 1 || day > 29)
				throw WrongDateFormatException("Invalid day format for '" + date + "' February has 29 days in a leap year");
		}
		else if (day < 1 || day > 28)
			throw WrongDateFormatException("Invalid day format for '" + date + "' February has 28 days in a common year");
	}
}

BitcoinExchange::WrongDateFormatException::WrongDateFormatException(const std::string& msg) : message_(msg) {}

const char* BitcoinExchange::WrongDateFormatException::what() const throw() {
	return message_.c_str();
}
