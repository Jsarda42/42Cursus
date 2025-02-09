#include "ParseClientUtils.hpp"
#include <iostream>

void ParseClientUtils::ParseRequest(const std::string &request, std::map<std::string, std::string> &parsedData) {
	std::istringstream stream(request);
	std::string line;
	
	int i = 0;
	bool inHeaders = true;
	bool bodyStarted = false;
	
	while (std::getline(stream, line)) {
		if (inHeaders && line == "\r") {
			inHeaders = false;
			continue;
		}
		
		if (inHeaders) {
			if (i == 0)
				parseMethodPath(line, parsedData);
			else if (line.find("Host:") != std::string::npos)
				parseHostPort(line, parsedData);
			else if (line.find("Content-Type:") != std::string::npos) {
				if (parsedData.find("content-type") == parsedData.end()) {
					if(line[line.size() - 1] == '\r')
						parsedData["content-type"] = line.substr(14, line.size() - 15);
					else
						parsedData["content-type"] = line.substr(14);
				}
			}
			else if (line.find("Content-Length:") != std::string::npos)
				parsedData["content-length"] = line.substr(16);
		}
		else {
			if (!bodyStarted) {
				bodyStarted = true;
			}
			if (!line.empty()) {
				if (!parsedData["getBody"].empty()) {
					parsedData["getBody"] += "\n";
				}
				parsedData["getBody"] += line;
			}
		}
		i++;
	}
	parsedData["uri"] = "http://" + parsedData["host"] + ":" + parsedData["port"] + parsedData["url"];
}

void ParseClientUtils::parseMethodPath(const std::string &request, std::map<std::string, std::string> &parsedData) {
	std::istringstream lineStream(request);
	std::string url;
	std::string method;
	std::string version;
	lineStream >> method >> url >> version;
	parsedData["method"] = method;

	size_t questionPos = url.find('?');
	if (questionPos != std::string::npos) {
		parsedData["url"] = url.substr(0, questionPos);
		parsedData["args"] = url.substr(questionPos + 1);
	}
	else parsedData["url"] = url;
}

void ParseClientUtils::parseHostPort(const std::string &request, std::map<std::string, std::string> &parsedData) {
	std::istringstream lineStream(request);
	std::string tmp;
	lineStream >> tmp >> parsedData["host"];

	size_t colonPos = parsedData["host"].find(':');
	if (colonPos != std::string::npos)	{
		parsedData["port"] = parsedData["host"].substr(colonPos + 1);
		parsedData["host"] = parsedData["host"].substr(0, colonPos);
	}
	else
		parsedData["port"] = "80";
}
