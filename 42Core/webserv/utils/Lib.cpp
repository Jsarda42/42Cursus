/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lib.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:54:21 by edegraev          #+#    #+#             */
/*   Updated: 2025/01/07 14:46:36 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"
#include "colors.hpp"


Lib::Lib() {}

Lib::~Lib() {}

Lib::Lib(Lib const &src) {
	*this = src;
}

Lib &Lib::operator=(Lib const &rhs) {
	if (this != &rhs) {}
	return *this;
}


bool Lib::isUnit(char u) {
	if (u == 'K' || 'k')
		return true;
	else if (u == 'G' || 'g')
		return true;
	else if (u == 'M' || 'm')
		return true;
	return false;
}

bool Lib::isMainOptionKey(std::string key) {
	if (key == "host")
		return true;
	else if (key == "server_name")
		return true;
	else if (key == "listen")
		return true;
	else if (key == "root")
		return true;
	else if (key == "error")
		return true;
	else if (key == "client_max_body_size")
		return true;
	else return false;
}

int Lib::parsePort(std::string value) {
	for (size_t i = 0; i < value.size();i++) {
		if (!std::isdigit(value[i]))
			return -1;
	}
	size_t valuePos = value.find(' ');
	if (valuePos != std::string::npos) {
		return -1;
	}
	int port = std::atoi(value.c_str());
	if (port > 65535)
		return -1;
	return port;
}

int Lib::stoi(std::string str) {
	int result = 0;
	bool is_negative = false;
	size_t i = 0;

	if (str[i] == '+' || str[i] == '-')
	{
		is_negative = (str[i] == '-');
		++i;
	}
	for (size_t i = 0; i < str.length(); ++i)
	{
		char c = str[i];
		if (std::isdigit(c))
			result = result * 10 + (c - '0');
		else 
			continue;
		// else
			// throw std::invalid_argument("Invalid input: non-numeric character (" + std::string(1, c) + ")");
	
	}
	return is_negative ? -result : result;
}

float Lib::stof(std::string str)
{
	float result = 0.0f;
	float decimal_divisor = 1.0f;
	bool is_negative = false;
	bool decimal_found = false;
	size_t i = 0;

	if (str[i] == '+' || str[i] == '-')
	{
		is_negative = (str[i] == '-');
		++i;
	}

	for (size_t i = 0; i < str.length(); ++i)
	{
		char c = str[i];

		if (c == '.')
		{
			if (decimal_found) throw std::invalid_argument("Invalid input: multiple decimal points");
			decimal_found = true;
		}
		else if (std::isdigit(c))
		{
			if (decimal_found)
			{
				decimal_divisor *= 10.0f;
				result += (c - '0') / decimal_divisor;
			}
			else
				result = result * 10.0f + (c - '0');
		}
		else throw std::invalid_argument("Invalid input: non-numeric character");
	}
	return is_negative ? -result : result;
}

unsigned long Lib::stoul(std::string str)
{
	unsigned long result = 0;

	for (size_t i = 0; i < str.size(); ++i) {
		char c = str[i];
		if (c < '0' || c > '9')
			throw std::invalid_argument("Invalid argument: non-numeric character found");

		result = result * 10 + (c - '0');
	}

	return result;
}

bool Lib::parseHost(std::string& value) {
	size_t start = 0;
	size_t end = 0;
	int octetCount = 0;
	if (value == "localhost") {
		value = "127.0.0.1";
		return true ;
	}
	if (value.size() > 15)
		return false;
	while ((end = value.find('.', start)) != std::string::npos) {
		std::string octet = value.substr(start, end - start);
		if (octet.empty()) return false;
		for (size_t i = 0; i < octet.size(); ++i) {
			if (!isdigit(octet[i])) return false;
		}
		int num = std::atoi(octet.c_str());
		if (num > 255) return false;
		++octetCount;
		start = end + 1;
	}
	std::string octet = value.substr(start);
	if (octet.empty()) return false;
	for (size_t i = 0; i < octet.size(); ++i) {
		if (!isdigit(octet[i])) return false;
	}
	int num = std::atoi(octet.c_str());
	if (num > 255) return false;
	++octetCount;
	return octetCount == 4;
}

void Lib::trim(std::string& str) {
	str.erase(0, str.find_first_not_of(" \t"));
	str.erase(str.find_last_not_of(" \t") + 1);
}

double Lib::stod(std::string str)
{
	double result = 0.0;
	double decimal_divisor = 1.0;
	bool is_negative = false;
	bool decimal_found = false;

	size_t i = 0;

	if (str[i] == '+' || str[i] == '-')
	{
		is_negative = (str[i] == '-');
		++i;
	}
	for (size_t i = 0; i < str.length(); ++i)
	{
		char c = str[i];

		if (c == '.')
		{
			if (decimal_found) throw std::invalid_argument("Invalid input: multiple decimal points");
			decimal_found = true;
		}
		else if (std::isdigit(c))
		{
			if (decimal_found)
			{
				decimal_divisor *= 10;
				result += (c - '0') / decimal_divisor;
			}
			else result = result * 10 + (c - '0');
		}
		else if (!std::isspace(c))
			throw std::invalid_argument("Invalid input: non-numeric character");
	}
	return is_negative ? -result : result;
}

std::string Lib::to_string(int n)
{
	std::string result;
	bool is_negative = n < 0;

	if (is_negative) n = -n;
	while (n > 0)
	{
		result = static_cast<char>(n % 10 + '0') + result;
		n /= 10;
	}
	if (is_negative) result = '-' + result;
	return result;
}

bool Lib::isDirectory(const std::string& path) {
	struct stat info;
	if (stat(path.c_str(), &info) != 0) {
		std::cerr << REDD << "Erreur : impossible d'accéder au chemin : " << path << "\n" << RST;
		return false;
	}
	if ((info.st_mode & S_IFDIR) != 0) {
		return true;
	} else {
		return false;
	}
}

bool Lib::isIndexPresent(const std::string& path)
{
	std::string indexPath = path + "/index.html";
	return fileExists(indexPath);
}


std::string Lib::readFile(const std::string &filename) {
	std::ifstream file((filename).c_str());
	if (!file.is_open()) return "";

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

bool Lib::fileExists(const std::string &filename) {
	struct stat buffer;
	if (stat(filename.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode)) return true;
	return false;
}

bool Lib::isFile(const std::string& name) {
	size_t dotPos = name.find_last_of('.');
	return dotPos != std::string::npos && dotPos != 0 && dotPos != name.length() - 1;
}

std::string Lib::getDirectory(const std::string& url) {
	if (url.empty() || url == "/")
		return "/";

	size_t lastSlash = url.find_last_of('/');
	if (lastSlash == std::string::npos)
		return "/";

	std::string afterSlash = url.substr(lastSlash + 1);

	if (isFile(afterSlash))
		return url.substr(0, lastSlash + 1);
	
	if (!afterSlash.empty())
		return url + "/";

	return url;
}

