#include "Folder.hpp"
#include "colors.hpp"

// send folder because there is no file in the path
Folder::Folder(std::string path) : path_(path) {
	struct stat info;

	if (stat(path.c_str(), &info) != 0)
		std::cerr << REDD << "Cannot access " << path << std::endl << RST;
	else if (info.st_mode & S_IFDIR)
		;
	else
		std::cerr << REDD << path << " is not a directory" << std::endl << RST;
}

Folder::~Folder() {}

std::string Folder::html(const std::string &filename, const std::string &type) {
	return type + " <a href=\"" + filename + "\">" + filename + "</a><br>";
}

std::string Folder::ls() {
	DIR *dir;
	struct dirent *ent;
	std::string result;

	result = "<html><head><title>Index of " + path_ + "</title><meta charset=\"UTF-8\"></head><body>";
	if ((dir = opendir(path_.c_str())) != NULL) {
		result += "Listing of " + path_ + ":<br>\n";
		while ((ent = readdir(dir)) != NULL) {
			std::string fullPath = path_ + "/" + ent->d_name;

			if (ent->d_type == DT_DIR)
				result += html(ent->d_name, "📁") + "\n";
			else if (ent->d_type == DT_REG)
				result += html(ent->d_name, "📄") + "\n";
			else if (ent->d_type == DT_LNK)
				result += html(ent->d_name, "🔗") + "\n";
			else {
				// Use `stat` as a fallback for other types or if `d_type` is DT_UNKNOWN
				struct stat sb;
				if (stat(fullPath.c_str(), &sb) == 0) {
					if (S_ISDIR(sb.st_mode))
						result += html(ent->d_name, "📁") + "\n";
					else if (S_ISREG(sb.st_mode))
						result += html(ent->d_name, "📄") + "\n";
					else
						result += html(ent->d_name, "❓") + "\n";
				}
				else
					std::cerr << REDD << "Could not stat: " << fullPath << std::endl << RST;
					// result += "[?] " + std::string(ent->d_name) + "\n";
			}
		}
		closedir(dir);
	}
	else
		result += "Could not open directory " + path_ + "<br>";
	result += "</body></html>";
	return result;
}
