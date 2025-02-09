#pragma once

#include <string>
#include <sstream>
#include <map>

class ParseClientUtils {
	public:
		static void parseMethodPath(const std::string &request, std::map<std::string, std::string> &parsedData);
		static void parseHostPort(const std::string &request, std::map<std::string, std::string> &parsedData);
		static void ParseRequest(const std::string &request, std::map<std::string, std::string> &parsedData);
};

