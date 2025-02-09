#include "ParsedData.hpp"
#include "ParseStatusMessage.hpp"
#include "ParseType.hpp"
#include "colors.hpp"
#include "Lib.hpp"

ParsedData::ParsedData(void) {}

ParsedData::ParsedData(const ParsedData& cpy) : ClientRequest_(cpy.ClientRequest_) {
	servers_ = cpy.servers_;
}

ParsedData& ParsedData::operator=(const ParsedData& rhs) {
	if (this != &rhs) {
		ClientRequest_ = rhs.ClientRequest_;
		servers_ = rhs.servers_;
	}
	return *this;
}

ParsedData::~ParsedData(void) {}

void ParsedData::populateData(const std::string &request) {
	ClientRequest_.clear();
	ParseClientUtils::ParseRequest(request, ClientRequest_);
}

std::string ParsedData::getRequestHost() const {
	std::map<std::string, std::string>::const_iterator it = ClientRequest_.find("host");
	return (it != ClientRequest_.end()) ? it->second : "";
}

std::string ParsedData::getRequestPort() const {
	std::map<std::string, std::string>::const_iterator it = ClientRequest_.find("port");
	return (it != ClientRequest_.end()) ? it->second : "";
}

std::string ParsedData::getRequestMethod() const {
	std::map<std::string, std::string>::const_iterator it = ClientRequest_.find("method");
	return (it != ClientRequest_.end()) ? it->second : "";
}

std::string ParsedData::getRequestUrl() const {
	std::map<std::string, std::string>::const_iterator it = ClientRequest_.find("url");
	return (it != ClientRequest_.end()) ? it->second : "";
}

std::string ParsedData::getRequestArgs() const {
	std::map<std::string, std::string>::const_iterator it = ClientRequest_.find("args");
	return (it != ClientRequest_.end()) ? it->second : "";
}

std::string ParsedData::getRequestBody() const {
	std::map<std::string, std::string>::const_iterator it = ClientRequest_.find("getBody");
	return (it != ClientRequest_.end()) ? it->second : "";
}

std::string ParsedData::getContentType() const {
	std::map<std::string, std::string>::const_iterator it = ClientRequest_.find("content-type");
	return (it != ClientRequest_.end()) ? it->second : "";
}

std::string ParsedData::getContentLenght() const {
	std::map<std::string, std::string>::const_iterator it = ClientRequest_.find("content-length");
	return (it != ClientRequest_.end()) ? it->second : "";
}

std::string ParsedData::getRequestUri() const {
	std::map<std::string, std::string>::const_iterator it = ClientRequest_.find("uri");
	return (it != ClientRequest_.end()) ? it->second : "";
}

void ParsedData::printClientData() const {
	for (std::map<std::string, std::string>::const_iterator it = ClientRequest_.begin(); it != ClientRequest_.end(); ++it) {
		std::cout << it->first << " => " << it->second << std::endl;
	}
	std::cout << std::endl;
}

void ParsedData::printType(const std::string &url) const {
	std::cout << ParseType::getType(url) << std::endl;
}

std::string ParsedData::getType(const std::string &url) {
	return ParseType::getType(url);
}

std::string ParsedData::getStatusMessage(const std::string &error) {
		return ParseStatusMessage::getStatusMessage(error);
}

void ParsedData::printErrorMessage(const std::string &error) const {
	std::cout << ParseStatusMessage::getStatusMessage(error) << std::endl;
}

void ParsedData::printServers() const {
	for (std::vector<Server>::const_iterator it = servers_.begin(); it != servers_.end(); ++it)
		it->display();
}

void ParsedData::addServer(const Server& server) {
	servers_.push_back(server);
}

std::vector<int> ParsedData::getPossiblePorts(void) const {
    std::vector<int> ports; // Vector to store unique ports

    // Iterate over each server
    for (size_t i = 0; i < servers_.size(); ++i) {
        std::vector<int> serverPorts = servers_[i].getPorts();  // Get the list of ports for this server

        // Iterate over each port for the current server
        for (size_t j = 0; j < serverPorts.size(); ++j) {
            int port = serverPorts[j];  // Access individual port

            // If the port is not already in the 'ports' vector, add it
            bool found = false;
            for (size_t k = 0; k < ports.size(); ++k) {
                if (ports[k] == port) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                ports.push_back(port);
            }
        }
    }

    return ports;
}



Server ParsedData::getDefaultServer(int port) const {
    for (size_t i = 0; i < servers_.size(); ++i) {
        // Get the list of ports for the current server
        std::vector<int> serverPorts = servers_[i].getPorts();
        
        // Check if the server has no server name and contains the given port
        if (servers_[i].getServerName().empty()) {
            bool portFound = false;
            for (size_t j = 0; j < serverPorts.size(); ++j) {
                if (serverPorts[j] == port) {
                    portFound = true;
                    break;
                }
            }

            // If the port was found, return the server
            if (portFound) {
                return servers_[i];
            }
        }
    }

    // If no matching server is found, print an error and throw an exception
    std::cerr << REDD << "Error: No default server found for port " << port << "\n" << RST;
    throw std::runtime_error("No default server configured for this port.");
}


Server ParsedData::getServer(std::string server_name, int port) {
	if (port == 0)
		throw std::runtime_error("");
	for (size_t i = 0; i < servers_.size(); ++i) {
		if (std::find(servers_[i].getPorts().begin(), servers_[i].getPorts().end(), port) == servers_[i].getPorts().end()) continue;
		std::string serverNames = servers_[i].getServerName();
		size_t pos = serverNames.find(' ');

		if (pos != std::string::npos) {
			std::istringstream iss(serverNames);
			std::string singleName;
			while (iss >> singleName)
				if (singleName == server_name) return servers_[i];
		}
		else
			if (serverNames == server_name) return servers_[i];
	}
	try {
		return getDefaultServer(port);
	} catch (const std::exception& e) {
		throw std::runtime_error("No server found for " + server_name + ":" + Lib::to_string(port));
	}
}
