#pragma once
#include <iostream>
#include <map>

class BitcoinExchange {

	private:
		std::map<std::string, double> data_;
		std::map<std::string, std::string> date_;

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& cpy);
		BitcoinExchange& operator=(const BitcoinExchange& rhs);
		~BitcoinExchange(void);

		void initData(void);
		void processData(std::string inputFile);
		void parseDate(std::string date);
		bool parseLine(std::string line);
		void parseLineDate(std::string date);
		class WrongDateFormatException : public std::exception {
			private :
				std::string message_;

			public :
			 	virtual ~WrongDateFormatException() throw() {}
				WrongDateFormatException(const std::string& msg);
				virtual const char* what() const throw();
		};

};

