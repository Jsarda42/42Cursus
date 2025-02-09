#include "ServerLocation.hpp"

ServerLocation::ServerLocation(void) {
	listing_ = true;
}

ServerLocation::ServerLocation(const ServerLocation& cpy) {
		listing_ = cpy.listing_;
		index_ = cpy.index_;
		methods_ = cpy.methods_;
		path_ = cpy.path_;
		redirect_ = cpy.redirect_;
}

ServerLocation & ServerLocation::operator=(const ServerLocation& rhs) {
	if (this != &rhs) {
		listing_ = rhs.listing_;
		index_ = rhs.index_;
		methods_ = rhs.methods_;
		path_ = rhs.path_;
		redirect_ = rhs.redirect_;
	}
	return *this;
}

std::vector<std::string> ServerLocation::getMethods(void) const {
	return methods_;
}

std::string ServerLocation::getRedirect(void) const {
    return redirect_;
}

void ServerLocation::setPath(const std::string& path) {
	path_ = path;
}

void ServerLocation::setListing(bool value) {
	listing_ = value;
}

void ServerLocation::setMethods(const std::vector<std::string>& methods) {
	for (size_t i = 0; i < methods.size();i++)
		methods_.push_back(methods[i]);
}

void ServerLocation::setRedirect(const std::string& value) {
    redirect_ = value;
}
		
void ServerLocation::setIndex(const std::string& index) {
	index_ = index;
}

bool ServerLocation::getListing() const {
	return listing_;
}

std::string ServerLocation::getIndex() const {
	return index_;
}

std::string ServerLocation::getPath(void) const {
	return path_;
}

ServerLocation::~ServerLocation(void) {}

bool ServerLocation::isMethodAllowed(std::string requestMethod)
{
	if (methods_.size() == 0)
		return true;
	for (size_t i = 0; i < methods_.size(); ++i) {
		if (methods_[i] == requestMethod) {
			return true;
		}
	}
	return false;
}

std::ostream &operator<<(std::ostream &out, const ServerLocation &c) {
	out << "ServerLocation: " << std::endl;
	out << "- listing: " << c.getListing() << std::endl;
	out << "- index: " << c.getIndex() << std::endl;
	out << "- methods: ";
	std::vector<std::string> methods = c.getMethods();
	for (size_t i = 0; i < methods.size();i++)
		out << methods[i] << " ";
	out << std::endl;
	out << "- path: " << c.getPath() << std::endl;
	out << "- redirect: " << c.getRedirect() << std::endl;
	return out;
}
