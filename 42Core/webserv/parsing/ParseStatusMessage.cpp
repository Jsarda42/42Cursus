#include "ParseStatusMessage.hpp"

ParseStatusMessage::ParseStatusMessage(void) {}

ParseStatusMessage::ParseStatusMessage(const ParseStatusMessage& cpy) {
	*this = cpy;
}

ParseStatusMessage& ParseStatusMessage::operator=(const ParseStatusMessage& rhs) {
		if (this != &rhs)
		return *this;
	return *this;
}

std::map<std::string, std::string> ParseStatusMessage::loadErrors() {
	std::map<std::string, std::string> typesData;
	typesData["100"] = "Continue";
	typesData["101"] = "Switching Protocol";
	typesData["102"] = "Processing";
	typesData["103"] = "Early Hints";
	typesData["200"] = "OK";
	typesData["201"] = "Created";
	typesData["202"] = "Accepted";
	typesData["203"] = "Non-Authoritative Information";
	typesData["204"] = "No Content";
	typesData["205"] = "Reset Content";
	typesData["206"] = "Partial Content";
	typesData["207"] = "Multi-Status";
	typesData["208"] = "Already Reported";
	typesData["226"] = "IM Used";
	typesData["300"] = "Multiple Choices";
	typesData["301"] = "Moved Permanently";
	typesData["302"] = "Found";
	typesData["303"] = "See Other";
	typesData["304"] = "Not Modified";
	typesData["307"] = "Temporary Redirect";
	typesData["308"] = "Permanent Redirect";
	typesData["400"] = "Bad Request";
	typesData["401"] = "Unauthorized";
	typesData["402"] = "Payment Required";
	typesData["403"] = "Forbidden";
	typesData["404"] = "Not Found";
	typesData["405"] = "Method Not Allowed";
	typesData["406"] = "Not Acceptable";
	typesData["407"] = "Proxy Authentication Required";
	typesData["408"] = "Request Timeout";
	typesData["409"] = "Conflict";
	typesData["410"] = "Gone";
	typesData["411"] = "Length Required";
	typesData["412"] = "Precondition Failed";
	typesData["413"] = "Payload Too Large";
	typesData["414"] = "URI Too Long";
	typesData["415"] = "Unsupported Media Type";
	typesData["416"] = "Range Not Satisfiable";
	typesData["417"] = "Expectation Failed";
	typesData["418"] = "I'm a teapot";
	typesData["421"] = "Misdirected Request";
	typesData["422"] = "Unprocessable Entity";
	typesData["423"] = "Locked";
	typesData["424"] = "Failed Dependency";
	typesData["425"] = "Too Early";
	typesData["426"] = "Upgrade Required";
	typesData["428"] = "Precondition Required";
	typesData["429"] = "Too Many Requests";
	typesData["431"] = "Request Header Fields Too Large";
	typesData["451"] = "Unavailable For Legal Reasons";
	typesData["500"] = "Internal Server Error";
	typesData["501"] = "Not Implemented";
	typesData["502"] = "Bad Gateway";
	typesData["503"] = "Service Unavailable";
	typesData["504"] = "Gateway Timeout";
	typesData["505"] = "HTTP Version Not Supported";
	typesData["506"] = "Variant Also Negotiates";
	typesData["507"] = "Insufficient Storage";
	typesData["508"] = "Loop Detected";
	typesData["510"] = "Not Extended";
	typesData["511"] = "Network Authentication Required";
	return (typesData);
}

std::string ParseStatusMessage::getStatusMessage(const std::string &error) {
		std::map<std::string, std::string> typesData = loadErrors();
		std::map<std::string, std::string>::iterator it = typesData.find(error);
		if (it != typesData.end())
			return (it->second);
		return ("No signal");
}

ParseStatusMessage::~ParseStatusMessage(void) {}
