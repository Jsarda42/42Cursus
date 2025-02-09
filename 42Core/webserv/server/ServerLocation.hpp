#pragma once

#include <iostream>
#include <vector>

class ServerLocation {

	private:
		bool listing_;
		std::string index_;
		std::vector<std::string> methods_;
		std::string path_;
		std::string redirect_;

	public:
		ServerLocation(void);
		ServerLocation(const ServerLocation& cpy);
		ServerLocation & operator=(const ServerLocation& rhs);
		~ServerLocation(void);

		bool getListing() const;
		std::string getIndex() const;
		std::string getPath(void) const;
		std::vector<std::string> getMethods(void) const;
        std::string getRedirect(void) const;

		void setPath(const std::string& path);
		void setListing(bool value);
		void setMethods(const std::vector<std::string>& methods);
		void setRedirect(const std::string& value);
		void setIndex(const std::string& index);

		bool isMethodAllowed(std::string requestMethod);
};

std::ostream &operator<<(std::ostream &out, const ServerLocation &c);