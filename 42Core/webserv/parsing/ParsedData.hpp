#pragma once

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "ParseClientUtils.hpp"
#include "Server.hpp"
#include <algorithm>

class ParsedData {

	private:
		std::map<std::string, std::string> ClientRequest_;
		std::vector<Server> servers_;

	public:
		ParsedData(void);
		ParsedData(const ParsedData& cpy);
		ParsedData& operator=(const ParsedData& rhs);
		~ParsedData(void);

		// server
		void addServer(const Server& server);
		Server getServer(std::string server_name, int port);
		Server getDefaultServer(int port) const;

		std::vector<int> getPossiblePorts(void) const;

		// getter for the client request
		void populateData(const std::string &request);
		std::string getRequestHost() const;
		std::string getRequestPort() const;
		std::string getRequestMethod() const;
		std::string getRequestUrl() const;
		std::string getRequestUri() const;
		std::string getRequestArgs() const;
		std::string getRequestBody() const;
		std::string getContentType() const;
		std::string getContentLenght() const;

		// getter for the server
		static std::string getType(const std::string &url);
		static std::string getStatusMessage(const std::string &error);

		// print
		void printClientData() const;
		void printServers() const;
		void printErrorMessage(const std::string& error) const;
		void printType(const std::string& url) const;
};
