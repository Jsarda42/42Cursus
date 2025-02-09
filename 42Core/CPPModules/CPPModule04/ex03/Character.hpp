#pragma once
#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <iostream>

class Character : public ICharacter
{
	private:

		std::string name_;
		AMateria *items_[4];
		AMateria* unequippedItems_[10];
		int unequippedCount_;

	public:

		Character(void);
		Character(const std::string& name);
		Character(const Character &cpy);
		Character &operator=(const Character &rhs);
		~Character(void);

		std::string const &getName() const;
		void equip(AMateria *m);
		void unequip(int idx);
		void use(int idx, ICharacter &target);
};
