#include "Server.hpp"
#include <sstream>
#include "Lib.hpp"
#include "colors.hpp"

Server::Server(void) {
	client_max_body_size_ = -1;
}
Server::~Server(void) {}

Server::Server(const Server& cpy) {
	host_ = cpy.host_;
	server_name_ = cpy.server_name_;
	ports_ = cpy.ports_;
	root_ = cpy.root_;
	errorFiles_ = cpy.errorFiles_;
	client_max_body_size_ = cpy.client_max_body_size_;
	locations_ = cpy.locations_;
}

Server& Server::operator=(const Server& rhs) {

	if (this == &rhs)
		return *this;
	host_ = rhs.host_;
	server_name_ = rhs.server_name_;
	ports_ = rhs.ports_;
	root_ = rhs.root_;
	errorFiles_ = rhs.errorFiles_;
	client_max_body_size_ = rhs.client_max_body_size_;
	locations_ = rhs.locations_;

	return *this;
}

void Server::addLocation(const ServerLocation& location) {
		locations_.push_back(location);
}

std::string Server::getHost() const {
	return host_;
}

std::string Server::getServerName() const {
	return server_name_;
}

const std::vector<int>& Server::getPorts() const {
    return ports_;
}

double Server::getClientMaxBodySize(void) const {
	return client_max_body_size_;
}

std::string Server::getErrorFile(const int error) const {
	std::map<int, std::string>::const_iterator it = errorFiles_.find(error);
	if (it != errorFiles_.end()) return it->second;
	throw std::runtime_error("No error number found for error:" + Lib::to_string(error));
}


std::string Server::getRoot() const {
	return root_;
}

void Server::setHost(const std::string& host) {
	host_ = host;
}

void Server::setServerName(const std::string& server_name) {
	server_name_ = server_name;
}

double Server::getContentLenght() const {
	return client_max_body_size_;
}

void Server::setRoot(const std::string& root) {
	root_ = root;
}

void Server::setPort(int port) {
        ports_.push_back(port);
}

void Server::setErrorFiles(const std::string& error, int nb) {
	if (error.empty()) throw std::runtime_error("Error string cannot be empty");
	if (nb <= 0) throw std::runtime_error("Error number must be positive");
	errorFiles_[nb] = error;
}

ServerLocation Server::getLocationConfig(std::string path) {
	for (size_t i = 0; i < locations_.size();i++) {
		if (locations_[i].getPath()[locations_[i].getPath().size() - 1] == '/') {
			if (locations_[i].getPath() == path)
				return locations_[i];
		}
		else if (locations_[i].getPath() + "/" == path)
			return locations_[i];
	}
	throw std::runtime_error("No LocationConfig found with path");
}

void Server::setClientMaxBodySize(const std::string& client_max_body_size) {
	std::string num;
	char u = 'o';
	for (size_t i = 0; i < client_max_body_size.size();i++) {
		if (std::isdigit(client_max_body_size[i]))
			num += client_max_body_size[i];
		else if (!std::isdigit(client_max_body_size[i]) && Lib::isUnit(client_max_body_size[i])) {
			u = client_max_body_size[i];
			break ;
		}
	}
	if (u == 'K' || u == 'k')
		client_max_body_size_ =  std::atol(num.c_str()) * 1000;
	else if (u == 'M' || u == 'm')
		client_max_body_size_ =  std::atol(num.c_str()) * 1000000;
	else if (u == 'G' || u == 'g')
		client_max_body_size_ =  std::atol(num.c_str()) * 1000000000;
	else
		client_max_body_size_ = std::atol(num.c_str()) * 1;
}

void Server::display() const
{
	std::cout << "Host: " << host_ << "\n";

	// display ports
	std::cout << "Ports: ";
	for (size_t i = 0; i < ports_.size(); ++i) {
		std::cout << ports_[i];
		if (i < ports_.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "\n";

	// general information
	std::cout << "Server Name: " << server_name_ << "\n"
			  << "Root: " << root_ << "\n";

	// error files
	std::cout << "Error Files:\n";
	for (std::map<int, std::string>::const_iterator it = errorFiles_.begin(); it != errorFiles_.end(); ++it) {
		std::cout << "  Error Number: " << it->first
				  << ", File: " << it->second << "\n";
	}

	// locations config
	for (size_t i = 0; i < locations_.size(); ++i) {
		std::cout << REDD << "Location config:\n" << RST;
		std::cout << "  Index: " << locations_[i].getIndex() << "\n"
				  << "  Listing: " << locations_[i].getListing() << "\n"
				  << "  Path: " << locations_[i].getPath() << "\n";
	}
}

