#include "ReplaceLine.hpp"

ReplaceLine::ReplaceLine( void ){
}

ReplaceLine::~ReplaceLine( void ){
}

std::string ReplaceLine::replaceLine(std::string line, std::string s1, std::string s2){

	size_t position = line.find(s1);

	for (size_t i = 0; i < line.size(); i++){
		if (position != std::string::npos) {
			line.erase(position, s1.size());
			line.insert(position, s2);
			position = line.find(s1, position + s2.size());
		}
	}
	return (line);
}
