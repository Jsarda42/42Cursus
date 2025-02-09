#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "ServerLocation.hpp"

class Server {

	private:
		std::vector<ServerLocation> locations_;
		std::string host_;
		std::string server_name_;
		std::vector<int> ports_;
		std::string root_;
		std::map<int, std::string> errorFiles_;
		double client_max_body_size_;

	public:
		Server(void);
		Server(const Server& cpy);
		Server & operator=(const Server& rhs);
		~Server(void);

		void addLocation(const ServerLocation& location);
		// getter
		std::string getHost(void) const;
		std::string getServerName(void) const;
		std::string getErrorFile(int error) const;
		std::string getRoot(void) const;
		const std::vector<int>& getPorts() const;
		double getClientMaxBodySize(void) const;
		double getContentLenght(void) const;
		ServerLocation getLocationConfig(std::string path);
	
		// // setter
		void setHost(const std::string& host);
		void setErrorFiles(const std::string &error, int nb);
		void setServerName(const std::string& ServerName);
		void setPort(int port);
		void setRoot(const std::string& root);
		void setClientMaxBodySize(const std::string& client_max_body_size);

		// // print
		void display() const;
};
