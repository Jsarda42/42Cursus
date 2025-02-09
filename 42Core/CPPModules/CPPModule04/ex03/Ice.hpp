#pragma once
#include "AMateria.hpp"
#include "ICharacter.hpp"

class ICharacter;

class Ice : public AMateria {

	private:

		std::string type_;

	public:

		Ice(void);
		Ice(const Ice& cpy);
		Ice& operator=(const Ice& rhs);
		~Ice(void);

		AMateria* clone() const;
		void use(ICharacter& target);
};
