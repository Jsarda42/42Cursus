#include "AMateria.hpp"

AMateria::AMateria(void) : type_("default") {
	//std::cout << "Creating " << type_ << " Amateria" << std::endl;
}

AMateria::AMateria(const std::string &type) : type_(type) {
	//std::cout << "Creating " << type_ << " Amateria" << std::endl;
}

AMateria& AMateria::operator=(const AMateria& rhs) {
	//std::cout << "operator = constructor Amateria call" << std::endl;
	if (this != &rhs)
		type_ = rhs.type_;
	return (*this);
}

AMateria::AMateria(const AMateria &cpy) {
	std::cout << "Cpy constructor Amateria call" << std::endl;
	*this = cpy;
}

AMateria::~AMateria(void) {
	//std::cout << "Destructor Amateria call" << std::endl;
}

std::string const& AMateria::getType() const {
	return (type_);
}
