#include "HttpServer.hpp"

std::string HttpServer::reponse(int code, const std::string &fileContent, const std::string &filePath)
{
	std::string http_response =
		"HTTP/1.1 " + Lib::to_string(code) + " " + ParsedData::getStatusMessage(Lib::to_string(code)) + "\r\n"
		"Content-Type: " + ParsedData::getType(filePath) + "\r\n"
		"Content-Length: " + Lib::to_string(fileContent.size()) + "\r\n"
		"\r\n" + fileContent;
	return http_response;
}

void HttpServer::sendRedirect(int client_socket, const std::string &uri)
{
	std::string http_response =
		"HTTP/1.1 301 " + ParsedData::getStatusMessage("301") + "\r\n"
		"Location: " + uri + "\r\n"
		"\r\n";
	std::cout << ORNG << "[301] Redirect to " << uri << RST << std::endl;
	send(client_socket, http_response.c_str(), http_response.size(), 0);
	close(client_socket);
}

void HttpServer::sendLs(int client_socket, const std::string &filePath, ParsedData parsedData)
{
	if (filePath[filePath.size() - 1] != '/')
	{
		sendRedirect(client_socket, parsedData.getRequestUri() + "/");
		return;
	}

	try
	{
		Folder folder(filePath);
		std::string result = folder.ls();

		std::string http_response =
			"HTTP/1.1 200 " + ParsedData::getStatusMessage("200") + "\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: " + Lib::to_string(result.size()) + "\r\n"
			"\r\n" + result;
		std::cout << GRNN << "[200] Directory listing: " << filePath << RST << std::endl;
		send(client_socket, http_response.c_str(), http_response.size(), 0);
		close(client_socket);
	}
	catch (const std::exception &e)
	{
		std::cerr << REDD << e.what() << '\n' << RST;
		std::string http_response = reponse(404, "404 Not Found | webserv", filePath);
		std::cout << REDD << "[404] " << filePath << RST << std::endl;
		send(client_socket, http_response.c_str(), http_response.size(), 0);
		close(client_socket);
	}
}

bool HttpServer::isReqBodyOversize(ParsedData parsedData, Server confNode, int client_socket)
{
	return false;
	double request_body_size = Lib::stod(parsedData.getContentLenght());
	double maxBodySize = confNode.getClientMaxBodySize();
	if(maxBodySize == -1)
		return false;
	if (request_body_size > maxBodySize) {
		std::cout << REDD << "[413] " << std::fixed << std::setprecision(0) << request_body_size << "/" << maxBodySize << RST << std::endl;
		sendCodeFileOrMessage(client_socket, 413, "", confNode);
		return true;
	}
	std::cout << std::fixed << std::setprecision(0) << request_body_size << "/" << maxBodySize << std::endl;
	return false;
}

bool HttpServer::isReqPhp(ParsedData parsedData, std::string filePath, int client_socket)
{
	if (filePath.substr(filePath.find_last_of(".") + 1) != "php")
		return false;

	Php php;
	php.createEnv(parsedData, filePath);

	std::string result = php.askPhp();

	if(result == "Time out")
	{
		sendCodeFileOrMessage(client_socket, 408, "", conf_.getServer(parsedData.getRequestHost(), Lib::stoi(parsedData.getRequestPort())));
		return true;
	}
	
	// seperating the header from the body
	std::string::size_type pos = result.find("\r\n\r\n");
	std::string header = result.substr(0, pos);
	std::string body = result.substr(pos + 4);

	std::string http_response =
		"HTTP/1.1 200 OK\r\n"
		+ header + "\r\n"
		"Content-Length: " + Lib::to_string(body.size()) + "\r\n"
		"\r\n" + body;
	std::cout << LIME << "[200] " << filePath << RST << std::endl;
	send(client_socket, http_response.c_str(), http_response.size(), 0);
	close(client_socket);
		
	return true;
}

void HttpServer::handleRequest(int client_fd, ClientData clientData)
{
	// std::cout << "Received header " << clientData.header.size() << " bytes:\n" << clientData.header << std::endl;
	// std::cout << "Received body " << clientData.body.size() << " bytes:\n" << clientData.body << std::endl;

	int client_socket = client_fd;

	std::string response = "HTTP/1.1 200 OK\r\n";
	response += "Content-Length: 13\r\n";
	response += "Content-Type: text/plain\r\n\r\n";
	response += "Hello, World!";

	// send(client_fd, response.c_str(), response.size(), 0);
	// close(client_fd);
	// return;

	ParsedData parsedData;
	parsedData.populateData(clientData.header + "\r\n\r\n" + clientData.body);

	if(parsedData.getRequestHost().empty() || (parsedData.getRequestPort().empty()))
	{
		try
		{
			sendCodeFileOrMessage(client_socket, 400, "", conf_.getServer(parsedData.getRequestHost(), Lib::stoi(parsedData.getRequestPort())));
		}
		catch(const std::exception& e)
		{
			close(client_socket);
			return;
		}
	}

	Server confNode;
	try
	{
		confNode = conf_.getServer(parsedData.getRequestHost(), Lib::stoi(parsedData.getRequestPort()));
	}
	catch(const std::exception& e)
	{
		sendCodeFileOrMessage(client_socket, 501, "", confNode);
	}
	if (isReqBodyOversize(parsedData, confNode, client_socket))
		return;
		
	// load rules from the location
	ServerLocation locationConf;
	try {
		locationConf = confNode.getLocationConfig(Lib::getDirectory(parsedData.getRequestUrl()));
	}
	catch(const std::exception& e)
	{
		std::cerr << REDD << e.what() << '\n' << RST;
	}
	if (locationConf.getPath() != "")
		std::cout << locationConf << std::endl;

	if (!locationConf.isMethodAllowed(parsedData.getRequestMethod()))
		sendCodeFileOrMessage(client_socket, 405, "", confNode);
		
	// check redirection
	if (!locationConf.getRedirect().empty())
	{
		sendRedirect(client_socket, locationConf.getRedirect());
		return;
	}
	std::string url = parsedData.getRequestUrl();
	std::string rootPath = confNode.getRoot();
	// check index
	if(locationConf.getIndex() != "" && Lib::isDirectory(rootPath + url))
	{
		std::string index = locationConf.getIndex();
		if (index[0] == '/')
			index = index.substr(1);
		if (index[index.size() - 1] == '/')
			index = index.substr(0, index.size() - 1);
		if (url[url.size() - 1] == '/')
			url += index;
		else
			url += "/" + index;
	}
	else if(Lib::isIndexPresent(rootPath + url)) {
		if (url[url.size() - 1] == '/')
		 url += "index.html";
		else
		 url += "/index.html";
	}

	std::string filePath = rootPath + url;

	if (Lib::fileExists(filePath) && !Lib::isDirectory(filePath))
	{
		if (isReqPhp(parsedData, filePath, client_socket))
			return;

		// Envoyer un fichier si c'est un fichier valide
		std::string fileContent = Lib::readFile(filePath);
		std::string http_response = reponse(200, fileContent, filePath);
		std::cout << LIME << "[200] " << filePath << RST << std::endl;
		send(client_socket, http_response.c_str(), http_response.size(), 0);
		close(client_socket);
		return;
	}

	// Si c'est un dossier, tenter de lister les fichiers
	if (Lib::isDirectory(filePath))
	{
		try {
			if (locationConf.getListing())
			{
				sendLs(client_socket, filePath, parsedData);
				return;
			}
			std::cout << "listing is false " << std::endl;
		}
		catch (const std::exception &e){
			std::cerr << REDD << e.what() << '\n' << RST;
			sendLs(client_socket, filePath, parsedData);
			return;
		}
	}

	sendCodeFileOrMessage(client_socket, 404, filePath, confNode);
}

void HttpServer::sendCodeFileOrMessage(int client_socket, const int code, const std::string &filePath, const Server confNode)
{
	try {
		std::string errorFile = confNode.getErrorFile(code);
		std::string errorFilePath = confNode.getRoot() + "/" + errorFile;
		if(confNode.getRoot()[confNode.getRoot().size() - 1] == '/' || filePath[0] == '/')
			errorFile = confNode.getRoot() + errorFile;
		else
			errorFile = confNode.getRoot() + "/" + errorFile;
		errorFile = Lib::readFile(errorFilePath);
		if (errorFile.empty())
		{
			throw std::runtime_error("Error file " + errorFilePath + " not found");
		}
		std::string http_response = reponse(code, errorFile, errorFilePath);
		std::cout << SALM << "[" << code << "] " << filePath << RST << std::endl;
		send(client_socket, http_response.c_str(), http_response.size(), 0);
		close(client_socket);
	}
	catch (const std::exception &e)
	{
		std::cerr << REDD << e.what() << '\n' << RST;
		std::string data = Lib::to_string(code) + " " + ParsedData::getStatusMessage(Lib::to_string(code)) + " | webserv";
		std::string http_response = reponse(code, data, filePath);
		std::cout << SALM << "[" << code << "] " << filePath << RST << std::endl;
		send(client_socket, http_response.c_str(), http_response.size(), 0);
		close(client_socket);
	}
}
