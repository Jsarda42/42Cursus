#include "ParseConfig.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include "Lib.hpp"
#include "colors.hpp"
#include "ServerLocation.hpp"

ParseConfig::ParseConfig() {}

ParseConfig::ParseConfig(const std::string ConfigFile) : configFile_(ConfigFile) {
}

ParseConfig::ParseConfig(const ParseConfig& cpy) {
	configFile_ = cpy.configFile_;
}

ParseConfig& ParseConfig::operator=(const ParseConfig& rhs) {
	if (this == &rhs)
		return *this;
	configFile_ = rhs.configFile_;
	return *this;
}

ParseConfig::~ParseConfig() {}

void ParseConfig::handleMainOption(const std::string key, std::string value, Server &currentConfig, const int lineNumber) {
	if (!value.empty() && value[value.size() - 1] == ';') value.erase(value.size() - 1);
	if (key == "host") {
		if (!Lib::parseHost(value)) throw ErrorConfException("Invalid IP format.", lineNumber);
		currentConfig.setHost(value);
	}
	else if (key == "server_name") currentConfig.setServerName(value);
	else if (key == "listen") {
		int port = Lib::parsePort(value);
		if (port < 1) throw ErrorConfException("Invalid port format.", lineNumber);
			currentConfig.setPort(port);
	}
	else if (key == "root") currentConfig.setRoot(value);
	else if (key == "error") {
		size_t pos2 = value.find(' ');
		if (pos2 == std::string::npos) throw ErrorConfException("Invalid error format.", lineNumber);
		std::string errorNB = value.substr(0, pos2);
		std::string errorFileName = value.substr(pos2 + 1);
		checkOneValueOnly(errorFileName, lineNumber);
		if (errorFileName.empty())
			throw std::runtime_error("Missing fileName");
		currentConfig.setErrorFiles(errorFileName, std::atoi(errorNB.c_str()));
	}
	else if (key == "client_max_body_size") {
		currentConfig.setClientMaxBodySize(value);
		checkOneValueOnly(value, lineNumber);
	}
}

void ParseConfig::checkOneValueOnly(std::string value, const int lineNumber) {
	size_t pos = value.find(' ');
	if (pos != std::string::npos) throw ErrorConfException("Invalid error format.", lineNumber);
}

bool ParseConfig::wrongMethods(std::string value) {
	if (value != "GET" && value != "POST" && value != "DELETE")
		return true;
	return false;
}

std::vector<std::string> ParseConfig::parseMethods(std::string value, int lineNumber) {
	std::vector<std::string> methods;
	size_t startPos = 0;
	checkOneValueOnly(value, lineNumber);
	while (true) {
		size_t pos = value.find(',', startPos);
		if (pos == std::string::npos) {
			if (wrongMethods(value.substr(startPos, pos - startPos)))
				throw ErrorConfException("Invalid methods.", lineNumber);
			methods.push_back(value.substr(startPos));
			break;
		}
		if (wrongMethods(value.substr(startPos, pos - startPos)))
			throw ErrorConfException("Invalid methods.", lineNumber);
		methods.push_back(value.substr(startPos, pos - startPos));
		startPos = pos + 1;
	}

	if (methods.empty()) throw ErrorConfException("Invalid error format.", lineNumber);

	return methods;
}

void ParseConfig::handleLocation(std::string key, std::string value, ServerLocation &currentConfig, int lineNumber) {
	if (!value.empty() && value[value.size() - 1] == ';') value.erase(value.size() - 1);
	if (key == "path"){
		if (value.empty())
			throw ErrorConfException("Invalid path", lineNumber);
		currentConfig.setPath(value);
	}
	else if (key == "method") currentConfig.setMethods(parseMethods(value, lineNumber));
	else if (key == "listing") {
		checkOneValueOnly(value, lineNumber);
		if (value != "true" && value != "false")
			throw ErrorConfException("Invalid listing, should be a boolean", lineNumber);
		if (value == "true")
			currentConfig.setListing(true);
		else
			currentConfig.setListing(false);
	}
	else if (key == "index") {
		checkOneValueOnly(value, lineNumber);
		currentConfig.setIndex(value);
	}
	else if (key == "redirect") currentConfig.setRedirect(value);
	else throw ErrorConfException("Unknown location directive: " + key, lineNumber);
}

void ParseConfig::checkIfKeyMissing(const Server currentConfig, int lineNumber) {
	if (currentConfig.getHost().empty())
		throw ErrorConfException("Missing Host in server block", lineNumber);
	std::vector<int> ports = currentConfig.getPorts();
    if (ports.empty()) {
        throw ErrorConfException("Missing Port in server block.", lineNumber);
    }
	for (size_t i = 0; i < ports.size(); ++i) {
    	for (size_t j = i + 1; j < ports.size(); ++j) {
            if (ports[i] == ports[j]) {
                throw ErrorConfException("Duplicate port found in server block.", lineNumber);
            }
        }
    }
	if (currentConfig.getRoot().empty())
				throw ErrorConfException("Missing Root in server block.", lineNumber);
}

void ParseConfig::parseConfig(ParsedData& parsedData) {
	std::ifstream file(configFile_.c_str());
	if (!file.is_open()) throw ErrorConfException("Couldn't open file: " + configFile_, -1);
	if (file.peek() == std::ifstream::traits_type::eof()) throw ErrorConfException("Configuration file is empty.", -1);
	bool inServerBlock = false;
	bool inLocationBlock = false;
	Server currentConfig;
	ServerLocation LocationConfig;
	std::string line;
	int lineNumber = 0;
	int openBracesCount = 0;
	// vector to store the port
	// when we in server block we store all the port in the vector
	// when we finish to store all the port we check there is no duplicate port on the vectore if there is we throw an error 

	// we need to clear the vector before we start the next server block
	
	while (std::getline(file, line)) {
		++lineNumber;
		Lib::trim(line);
		if (line.empty() || line[0] == '#') continue;
		if (line == "server {") {
			if (inServerBlock) throw ErrorConfException("Nested server block not allowed.", lineNumber);
			inServerBlock = true;
			openBracesCount++;
			currentConfig = Server();
			continue;
		}
		if (line == "}") {
			if (inLocationBlock) {
				currentConfig.addLocation(LocationConfig);
				if (LocationConfig.getPath().empty())
					throw ErrorConfException("Missing path in location block.", lineNumber);
				inLocationBlock = false;
			}
			else if (inServerBlock) {
				inServerBlock = false;
				checkIfKeyMissing(currentConfig, lineNumber);
				parsedData.addServer(currentConfig);
			}
			else throw ErrorConfException("Unexpected closing brace.", lineNumber);
			openBracesCount--;
			continue;
		}
		if (inServerBlock) {
			size_t pos = line.find(' ');
			if (pos == std::string::npos && !inLocationBlock) throw ErrorConfException("Invalid directive format.", lineNumber);
			std::string key = line.substr(0, pos);
			std::string value = (pos != std::string::npos) ? line.substr(pos + 1) : "";
			if (!inLocationBlock && Lib::isMainOptionKey(key)) {
				handleMainOption(key, value, currentConfig, lineNumber);
				continue;
			}
			if (line == "location {") {
				if (inLocationBlock) throw ErrorConfException("Nested location block not allowed.", lineNumber);
				inLocationBlock = true;
				openBracesCount++;
				LocationConfig = ServerLocation();
				continue;
			}
			if (inLocationBlock) {
				handleLocation(key, value, LocationConfig, lineNumber);
				continue;
			}
		}
		throw ErrorConfException("Directive outside of server block.", lineNumber);
	}
	if (openBracesCount != 0) throw ErrorConfException("Mismatched braces in configuration file.", lineNumber);
}


ParseConfig::ErrorConfException::ErrorConfException(const std::string& msg, int line) : formatted_message_(msg), line_(line) {
	if (line == -1) {
		std::ostringstream err;
		err << REDD << msg;
		formatted_message_ = err.str();
		return ;
	}
	std::ostringstream err;
	err << REDD << "on line " << line_ << " : " << REDD << msg;
	formatted_message_ = err.str();
}

const char* ParseConfig::ErrorConfException::what() const throw() {
	return formatted_message_.c_str();
}
