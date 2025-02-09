#pragma once
#include "AMateria.hpp"
#include "ICharacter.hpp"

class ICharacter;

class Cure : public AMateria {

	private:

		std::string type_;

	public:

		Cure(void);
		Cure(const Cure& cpy);
		Cure& operator=(const Cure& rhs);
		~Cure(void);

		AMateria* clone() const;
		void use(ICharacter& target);
};
