#pragma once

#include <string>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <arpa/inet.h>
#include <iomanip>
#include <poll.h>
#include <ctime>

#include "colors.hpp"
#include "Lib.hpp"
#include "ParsedData.hpp"
#include "Folder.hpp"
#include "Php.hpp"

class HttpServer {

	private:
		// TODO : a deplacer
		struct ClientData {
			std::string buffer;     // Données reçues jusqu'à présent
			bool header_parsed;     // Indique si le header a été complètement lu
			size_t content_length;  // Longueur du body (extrait du header)
			
			std::string host;
			int port;
			int client_max_body_size;
			std::time_t connection_start;

			std::string header;
			std::string body;
		};
		std::map<int, ClientData> client_buffers; // Associer chaque socket à ses données

		std::vector<int> listening_sockets_;
		std::vector<struct pollfd> poll_fds;
		ParsedData conf_;

		HttpServer(void);

		bool exceedsAuthorizedBodySize(int client_fd, size_t index, std::vector<pollfd>& poll_fds, std::map<int, ClientData>& client_buffers);


		void handleRequest(int client_fd, ClientData clientData);
		std::string reponse(int code, const std::string &fileContent, const std::string &filePath);
		
		void sendLs(int client_socket, const std::string &filePath, ParsedData parsedData);
		void sendRedirect(int client_socket, const std::string &uri);
		void sendCodeFileOrMessage(int client_socket, const int code, const std::string &filePath, const Server confNode);
		bool isReqBodyOversize(ParsedData parsedData, Server confNode, int client_socket);
		bool isReqPhp(ParsedData parsedData, std::string filePath, int client_socket);
		
		void acceptConnection(int listening_fd);
		void handleClientRequest(size_t index);		
		bool isListeningSocket(int fd);

	public:
		HttpServer(ParsedData conf);
		HttpServer(const HttpServer& cpy);
		HttpServer& operator=(const HttpServer& rhs);
		~HttpServer();

		void run();
};
