#pragma once

#include <map>
#include <iostream>
#include <map>

class ParseType {

	private:
		ParseType(void);
		ParseType(const ParseType& cpy);
		ParseType& operator=(const ParseType& rhs);

	public:
		static std::map<std::string, std::string> loadAllowedTypes();
		~ParseType(void);
		static std::string getType(const std::string &url);
};
