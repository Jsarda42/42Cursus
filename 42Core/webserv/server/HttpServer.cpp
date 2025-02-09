#include "HttpServer.hpp"

extern int g_sigcode;

HttpServer::HttpServer(const HttpServer& cpy) {
	conf_ = cpy.conf_;
	poll_fds = cpy.poll_fds;
}

HttpServer& HttpServer::operator=(const HttpServer& rhs) {
	if (this != &rhs) {
		conf_ = rhs.conf_;
		poll_fds = rhs.poll_fds;
	}
	return *this;
}

HttpServer::HttpServer(ParsedData conf) : conf_(conf)
{
	std::vector<int> ports = conf_.getPossiblePorts();
	for (size_t i = 0; i < ports.size(); ++i)
	{
		std::cout << "Setting up port: " << ports[i] << std::endl;
		int server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
		if(server_fd_ < 0)
		{
			perror("Socket failed");
			exit(EXIT_FAILURE);
		}

		// allow to reuse the same port
		int opt = 1;
		if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		{
			perror("setsockopt(SO_REUSEADDR) failed");
			exit(EXIT_FAILURE);
		}

		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(ports[i]);

		// link the socket
		if (bind(server_fd_, (struct sockaddr *)&address, sizeof(address)) < 0)
		{
			perror("Bind failed");
			exit(EXIT_FAILURE);
		}

		if (listen(server_fd_, SOMAXCONN) < 0) {
			perror("Listen failed");
			exit(EXIT_FAILURE);
		}
		std::cout << "Server listening on port " << ports[i] << std::endl;
		listening_sockets_.push_back(server_fd_);
		
		// pollfd pfd;
		// pfd.fd = server_fd_;
		// pfd.events = POLLIN;
		// pfd.revents = 0;
		// poll_fds.push_back(pfd);
		pollfd pfd = {0, 0, 0};
        pfd.fd = server_fd_;
        pfd.events = POLLIN;
        poll_fds.push_back(pfd);
	}
}

HttpServer::~HttpServer()
{
	std::cout << "Destructor called" << std::endl;
	for (size_t i = 0; i < listening_sockets_.size(); ++i)
		close(listening_sockets_[i]);
	listening_sockets_.clear();
}

bool HttpServer::isListeningSocket(int fd)
{
	for (size_t i = 0; i < listening_sockets_.size(); ++i)
		if (listening_sockets_[i] == fd)
			return true;
	return false;
}
/**
 * @brief Vérifie si une connexion utilise le protocole TLS/SSL.
 * 
 * Cette fonction analyse les premiers octets d'une connexion pour déterminer
 * si le client tente d'initier une communication TLS (par exemple via HTTPS).
 * Elle utilise le flag MSG_PEEK pour lire les données sans les retirer du tampon.
 * 
 * @param socket_fd Le descripteur de socket à vérifier.
 * @return true si la connexion correspond à une tentative TLS/SSL (ClientHello).
 * @return false sinon.
 * 
 * Le protocole TLS commence généralement par un message Handshake (0x16)
 * suivi de la version majeure du protocole (0x03 pour TLS 1.0, 1.1, 1.2, 1.3).
 */
bool isTLSHandshake(int socket_fd) {
	char buffer[5];
	int bytes_read = recv(socket_fd, buffer, sizeof(buffer), MSG_PEEK);
	if (bytes_read < 0) return false;

	// TLS ClientHello starts with 0x16 (Handshake) and a major version >= 3
	return (bytes_read >= 3 && buffer[0] == 0x16 && buffer[1] == 0x03);
}

bool HttpServer::exceedsAuthorizedBodySize(int client_fd, size_t index, std::vector<pollfd>& poll_fds, std::map<int, ClientData>& client_buffers)
{
    if (client_buffers[client_fd].client_max_body_size != -1 && client_buffers[client_fd].buffer.size() > static_cast<size_t>(client_buffers[client_fd].client_max_body_size)) {
        std::cerr << "Request body exceeds maximum allowed size (" << client_buffers[client_fd].client_max_body_size << " bytes)\n";

        // Répondre avec une erreur 413 (Payload Too Large)
        std::string response = "HTTP/1.1 413 Payload Too Large\r\n";
        response += "Content-Length: 0\r\n";
        response += "Connection: close\r\n\r\n";
        std::cout << REDD << "[413] " << client_buffers[client_fd].buffer.size() << "/" << client_buffers[client_fd].client_max_body_size << RST << std::endl;
        send(client_fd, response.c_str(), response.size(), 0);

        // Lire et ignorer les données restantes avant de fermer
        char temp_buffer[1024];
        while (read(client_fd, temp_buffer, sizeof(temp_buffer)) > 0);

        close(client_fd);
        poll_fds.erase(poll_fds.begin() + index);
        client_buffers.erase(client_fd);
        return true;
    }
    return false;
}

void HttpServer::handleClientRequest(size_t index)
{
    int client_fd = poll_fds[index].fd;

    // Vérifie si le temps de connexion dépasse 5 secondes
    std::time_t current_time = std::time(0);
    if (std::difftime(current_time, client_buffers[client_fd].connection_start) > 5.0) {
        std::cerr << "Client exceeded upload timeout (5 seconds)\n";

        // Répondre avec une erreur 408 (Request Timeout)
        std::string response = "HTTP/1.1 408 Request Timeout\r\n";
        response += "Content-Length: 0\r\n";
        response += "Connection: close\r\n\r\n";
        send(client_fd, response.c_str(), response.size(), 0);

        close(client_fd);
        poll_fds.erase(poll_fds.begin() + index);
        client_buffers.erase(client_fd);
        return;
    }

    char buffer[1024] = {0};
    ssize_t bytes_read = read(poll_fds[index].fd, buffer, sizeof(buffer) - 1);

    if (bytes_read <= 0) {
        if (bytes_read < 0) perror("Read failed");
        else std::cout << "Client disconnected\n";

        close(poll_fds[index].fd);
        poll_fds.erase(poll_fds.begin() + index);
        client_buffers.erase(poll_fds[index].fd);
        return;
    }

    client_buffers[client_fd].buffer.append(buffer, bytes_read);

    if (exceedsAuthorizedBodySize(client_fd, index, poll_fds, client_buffers))
        return;

    // Si le header n'est pas encore parsé
    if (!client_buffers[client_fd].header_parsed) {
        size_t header_end = client_buffers[client_fd].buffer.find("\r\n\r\n");
        if (header_end != std::string::npos) {
            client_buffers[client_fd].header = client_buffers[client_fd].buffer.substr(0, header_end + 4);
            client_buffers[client_fd].header_parsed = true;

            size_t host_length_pos = client_buffers[client_fd].header.find("Host: ");
            if (host_length_pos != std::string::npos) {
                size_t host_length_end = client_buffers[client_fd].header.find("\r\n", host_length_pos);
                std::string host_value = client_buffers[client_fd].header.substr(
                    host_length_pos + 6, host_length_end - (host_length_pos + 6));
                size_t colon_pos = host_value.find(':');
                if (colon_pos != std::string::npos)
                {
                    client_buffers[client_fd].host = host_value.substr(0, colon_pos);
                    client_buffers[client_fd].port = Lib::stoi(host_value.substr(colon_pos + 1));

                    // get current conf to setup client_max_body_size
                    Server confNode;
                    try
                    {
                        confNode = conf_.getServer(client_buffers[client_fd].host, client_buffers[client_fd].port);
                        client_buffers[client_fd].client_max_body_size = confNode.getClientMaxBodySize();
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << REDD << e.what() << '\n' << RST;
                        close(client_fd);
                        poll_fds.erase(poll_fds.begin() + index);
                        client_buffers.erase(client_fd);
                        return;
                    }
                }
            }
            else {
                std::cerr << "Host header not found\n";
                close(client_fd);
                poll_fds.erase(poll_fds.begin() + index);
                client_buffers.erase(client_fd);
                return;
            }

            size_t content_length_pos = client_buffers[client_fd].header.find("Content-Length: ");
            if (content_length_pos != std::string::npos) {
                size_t content_length_end = client_buffers[client_fd].header.find("\r\n", content_length_pos);
                std::string content_length_value = client_buffers[client_fd].header.substr(
                    content_length_pos + 16, content_length_end - (content_length_pos + 16));
                client_buffers[client_fd].content_length = Lib::stoi(content_length_value);

                if (exceedsAuthorizedBodySize(client_fd, index, poll_fds, client_buffers))
                    return;
            } else {
                client_buffers[client_fd].content_length = 0;
            }

            client_buffers[client_fd].buffer.erase(0, header_end + 4);
        } else {
            return;
        }
    }

    if (client_buffers[client_fd].buffer.size() >= client_buffers[client_fd].content_length) {
        client_buffers[client_fd].body = client_buffers[client_fd].buffer.substr(0, client_buffers[client_fd].content_length);

		handleRequest(client_fd, client_buffers[client_fd]);

        client_buffers.erase(client_fd);
        close(client_fd);
        poll_fds.erase(poll_fds.begin() + index);
    }
}

void HttpServer::acceptConnection(int listening_fd)
{
	sockaddr_in client_address = {};
    socklen_t client_len = sizeof(client_address);
    int client_socket = accept(listening_fd, reinterpret_cast<struct sockaddr*>(&client_address), &client_len);

    if (client_socket < 0) {
        perror("Accept failed");
        return;
    }

    std::cout << "New connection from "
              << inet_ntoa(client_address.sin_addr) << " on port "
              << ntohs(client_address.sin_port) << "\n";

    pollfd client_pfd = {0, 0, 0};
    client_pfd.fd = client_socket;
    client_pfd.events = POLLIN;
    poll_fds.push_back(client_pfd);

    // Ajout d'un nouveau client avec l'heure de connexion
    ClientData data;
    data.header_parsed = false;
    data.client_max_body_size = -1;
    data.content_length = 0;
    data.connection_start = std::time(0); // Initialisation du temps de connexion
    client_buffers[client_socket] = data;
}

void HttpServer::run() {
	while (true) {
		int timeout_ms = 100;
		int poll_result = poll(&poll_fds[0], poll_fds.size(), timeout_ms);

		if (g_sigcode == 2) {
			std::cout << "HTTP Server shutting down..." << std::endl;
			return;
		}

		if (poll_result < 0) {
			perror("Poll failed");
			exit(EXIT_FAILURE);
		}

		if (poll_result == 0) continue;

		for (size_t i = 0; i < poll_fds.size(); ++i) {
            if (!(poll_fds[i].revents & POLLIN)) continue;

            if (isListeningSocket(poll_fds[i].fd)) {
                acceptConnection(poll_fds[i].fd);
            } else {
				handleClientRequest(i);
            }
        }
	}
}
