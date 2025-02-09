#pragma once
#include <iostream>
#include <vector>
#include "ParsedData.hpp"

class ParseConfig {

	private:
		std::string configFile_;

	public:
		ParseConfig(void);
		ParseConfig(const std::string ConfigFile);
		ParseConfig(const ParseConfig& cpy);
		ParseConfig& operator=(const ParseConfig& rhs);
		~ParseConfig(void);

		void parseConfig(ParsedData& parsedData);
		void handleMainOption(const std::string key, std::string value, Server &currentConfig, const int lineNumber);
		void handleLocation(const std::string key, std::string value, ServerLocation &currentConfig, const int lineNumber);
		void checkOneValueOnly(const std::string value, const int lineNumber);
		void checkIfKeyMissing(const Server currentConfig, int lineNumber);
		std::vector<std::string> parseMethods(std::string value, int lineNumber);
		bool wrongMethods(std::string value);

		class ErrorConfException : public std::exception {
			private :
				std::string formatted_message_;
				int line_;

			public :
				virtual ~ErrorConfException() throw() {}
				ErrorConfException(const std::string &msg, int line);
				virtual const char* what() const throw();
		};
};
