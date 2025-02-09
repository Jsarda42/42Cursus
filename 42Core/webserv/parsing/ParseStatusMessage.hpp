#pragma once

#include <map>
#include <iostream>

class ParseStatusMessage {

	private:
		ParseStatusMessage(void);
		ParseStatusMessage(const ParseStatusMessage& cpy);
		ParseStatusMessage& operator=(const ParseStatusMessage& rhs);

	public:
		static std::map<std::string, std::string> loadErrors();
		~ParseStatusMessage(void);
		static std::string getStatusMessage(const std::string &error);
};
