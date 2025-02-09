#include "Character.hpp"

Character::Character(void) : name_("default"), unequippedCount_(0) {
	//std::cout << "Creating " << name_ << " Character" << std::endl;
	for (int i = 0; i < 4; i++)
		items_[i] = NULL;
	for (int i = 0; i < 10; ++i)
		unequippedItems_[i] = NULL;
}

Character::Character(const std::string& name) : name_(name), unequippedCount_(0) {
	//std::cout << "Creating " << name_ << " Character" << std::endl;
	for (int i = 0; i < 4; i++)
		items_[i] = NULL;
	for (int i = 0; i < 10; ++i)
		unequippedItems_[i] = NULL;
}


Character& Character::operator=(const Character &rhs) {
	//std::cout << "operator = constructor Character call" << std::endl;
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

Character::Character(const Character &cpy) {
	//std::cout << "operator = constructor Character call" << std::endl;
	name_ = cpy.name_;
	for (int i = 0; i < 4; i++) {
		if (cpy.items_[i] != NULL)
			this->items_[i] = cpy.items_[i]->clone();
		else
			this->items_[i] = NULL;
	}
}

Character::~Character(void) {
	for (int i = 0; i < 4; i++) {
		if (items_[i])
			delete items_[i];
	}
	for (int i = 0; i < unequippedCount_; i++) {
		delete unequippedItems_[i];
	}
}

const std::string& Character::getName() const {
	return (name_);
}

void Character::equip(AMateria *m) {
	if (m == NULL) {
		std::cout << "Cannot equip a null materia!" << std::endl;
		return ;
	}
	for (int i = 0; i < 4; i++) {
		if (items_[i] == NULL) {
			items_[i] = m;
			std::cout << "Equipped " << m->getType() << " to slot " << i << std::endl;
			return ;
		}
	}
	std::cout << "No free slots to equip the materia!" << std::endl;
}

void Character::unequip(int idx) {
	if (idx < 0 || idx >= 4 || items_[idx] == NULL) {
		std::cout << "Invalid index or empty slot. Cannot unequip!" << std::endl;
		return;
	}
	if (unequippedCount_ < 10) {
		unequippedItems_[unequippedCount_] = items_[idx];
		unequippedCount_++;
	} else {
		std::cout << "No more space to store unequipped materia!" << std::endl;
	}

	std::cout << "Unequipped materia " << items_[idx]->getType() << " from slot " << idx << std::endl;
	items_[idx] = NULL;
}

void Character::use(int idx, ICharacter &target) {
	if (idx < 0 || idx >= 4 || items_[idx] == NULL) {
		std::cout << "Invalid index or no materia in this slot!" << std::endl;
		return;
	}
	items_[idx]->use(target);
	std::cout << "Character " << name_ << " uses " << items_[idx]->getType() << std::endl;
}

