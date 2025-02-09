#include <iostream>
#include <map>
#include <string>
#include "ParseType.hpp"

ParseType::ParseType(void) {}

ParseType::ParseType(const ParseType& cpy) {
	*this = cpy;
}

ParseType& ParseType::operator=(const ParseType& rhs) {
	if (this != &rhs)
		return *this;
	return *this;
}

std::map<std::string, std::string> ParseType::loadAllowedTypes() {
	std::map<std::string, std::string> typesData;
	typesData[".html"] = "text/html";
	typesData[".htm"] = "text/html";
	typesData[".php"] = "text/html"; // A supprimer
	typesData[".css"] = "text/css";
	typesData[".js"] = "application/javascript";
	typesData[".json"] = "application/json";
	typesData[".xml"] = "application/xml";
	typesData[".txt"] = "text/plain";
	typesData[".csv"] = "text/csv";
	typesData[".yaml"] = "application/x-yaml";
	typesData[".md"] = "text/markdown";

	// Images
	typesData[".jpeg"] = "image/jpeg";
	typesData[".jpg"] = "image/jpeg";
	typesData[".png"] = "image/png";
	typesData[".gif"] = "image/gif";
	typesData[".bmp"] = "image/bmp";
	typesData[".webp"] = "image/webp";
	typesData[".svg"] = "image/svg+xml";
	typesData[".ico"] = "image/x-icon";
	typesData[".tiff"] = "image/tiff";
	typesData[".heif"] = "image/heif";
	typesData[".avif"] = "image/avif";

	// Audio
	typesData[".mp3"] = "audio/mpeg";
	typesData[".ogg"] = "audio/ogg";
	typesData[".wav"] = "audio/wav";
	typesData[".flac"] = "audio/flac";
	typesData[".aac"] = "audio/aac";
	typesData[".opus"] = "audio/opus";
	typesData[".midi"] = "audio/midi";

	// Video
	typesData[".mp4"] = "video/mp4";
	typesData[".webm"] = "video/webm";
	typesData[".ogg"] = "video/ogg";
	typesData[".avi"] = "video/x-msvideo";
	typesData[".mov"] = "video/quicktime";
	typesData[".mkv"] = "video/x-matroska";
	typesData[".flv"] = "video/x-flv";
	typesData[".wmv"] = "video/x-ms-wmv";
	typesData[".mpeg"] = "video/mpeg";
	typesData[".3gp"] = "video/3gpp";
	typesData[".mpg"] = "video/mpeg";

	// Fonts
	typesData[".woff"] = "font/woff";
	typesData[".woff2"] = "font/woff2";
	typesData[".ttf"] = "font/ttf";
	typesData[".otf"] = "font/otf";
	typesData[".eot"] = "application/vnd.ms-fontobject";
	typesData[".sfnt"] = "application/font-sfnt";

	// Compressed Files
	typesData[".zip"] = "application/zip";
	typesData[".tar"] = "application/x-tar";
	typesData[".gz"] = "application/gzip";
	typesData[".rar"] = "application/vnd.rar";
	typesData[".7z"] = "application/x-7z-compressed";
	typesData[".bz2"] = "application/x-bzip2";

	// Documents
	typesData[".pdf"] = "application/pdf";
	typesData[".doc"] = "application/msword";
	typesData[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	typesData[".xls"] = "application/vnd.ms-excel";
	typesData[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	typesData[".ppt"] = "application/vnd.ms-powerpoint";
	typesData[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	typesData[".rtf"] = "application/rtf";
	typesData[".epub"] = "application/epub+zip";
	typesData[".odt"] = "application/vnd.oasis.opendocument.text";
	typesData[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";

	// Executables
	typesData[".exe"] = "application/octet-stream";
	typesData[".apk"] = "application/vnd.android.package-archive";
	typesData[".bat"] = "application/x-msdos-program";
	typesData[".msi"] = "application/x-msi";

	// Other
	typesData[".jsonld"] = "application/ld+json";
	typesData[".webmanifest"] = "application/manifest+json";
	typesData[".ics"] = "text/calendar";
	typesData[".eml"] = "message/rfc822";

	return typesData;
}

std::string ParseType::getType(const std::string &url) {
	size_t pos = url.find_last_of(".");
	if (pos == std::string::npos)
		return ("text/plain");
	std::string extension = url.substr(pos);

	std::map<std::string, std::string> typesData = loadAllowedTypes();
	std::map<std::string, std::string>::iterator it = typesData.find(extension);
	if (it != typesData.end())
		return (it->second);
	return ("text/plain");
}

ParseType::~ParseType(void) {}
