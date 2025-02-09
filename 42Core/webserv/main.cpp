// #include "HttpServer.hpp"
#include "ParsedData.hpp"
#include "ParseConfig.hpp"
#include "HttpServer.hpp"
#include <iostream>
#include <signal.h>

int g_sigcode = 0;

void signal_handler(int signal_num)
{
	if (signal_num != SIGINT)
		return ;
	if (signal_num == SIGINT)
		g_sigcode = 2;
	std::cout << "The interrupt signal is (" << signal_num << "). \n";
	std::cout << "Server is shutting down...\n";
}

int main(int argc, char **argv) {
	std::string filename;
	if (argc != 2) {
		std::cout << "you did not define any config file : default file : config.txt\n";
		filename = "config.txt";
	}
	else filename = argv[1];
	signal(SIGINT, signal_handler);
	try {
		ParsedData parsedData;
		ParseConfig parser(filename);
		parser.parseConfig(parsedData);
		HttpServer server(parsedData);
		server.run();
	} catch (const std::exception& e) {
		std::cerr << REDD << "Error: " << e.what() << std::endl <<RST;
		return 1;
	}
	return 0;
}

