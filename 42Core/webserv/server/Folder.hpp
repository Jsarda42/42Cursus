#pragma once

#include <string>
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

class Folder {
	private:
		std::string path_;
		std::string html(const std::string &filename, const std::string &type);

	public:
		Folder(std::string path);
		~Folder();
		
		std::string ls();
};
