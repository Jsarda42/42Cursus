#include "MateriaSource.hpp"
#include "Cure.hpp"
#include "Ice.hpp"

MateriaSource::MateriaSource(void) {
	for (int i = 0; i < 4; i++) {
		learnedMateria_[i] = NULL;
	}
}
MateriaSource::~MateriaSource(void) {
	for (int i = 0; i < 4; i++) {
		if (learnedMateria_[i])
			delete learnedMateria_[i];
	}
	//std::cout << "MateriaSource destroyed" << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource& cpy) {
	*this = cpy;
}

MateriaSource& MateriaSource::operator=(const MateriaSource& rhs) {
	if (this != &rhs) {
		for (int i = 0; i < 4; i++) {
			delete learnedMateria_[i];
			learnedMateria_[i] = NULL;
		}

		for (int i = 0; i < 4; i++) {
			if (rhs.learnedMateria_[i] != NULL)
				learnedMateria_[i] = rhs.learnedMateria_[i]->clone();
		}
	}
		return (*this);
}

void MateriaSource::learnMateria(AMateria* src) {
	if (src == NULL) {
		std::cout << "Cannot learn a null materia!" << std::endl;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (learnedMateria_[i] == NULL) {
			learnedMateria_[i] = src;
			std::cout << "Learned materia of type: " << src->getType() << std::endl;
			return;
		}
	}
	std::cout << "No free slots to learn materia!" << std::endl;
}

AMateria* MateriaSource::createMateria(const std::string& type) {
	for (int i = 0; i < 4; i++) {
		if (learnedMateria_[i] && learnedMateria_[i]->getType() == type)
			return learnedMateria_[i]->clone();
	}
	std::cout << "Materia type " << type << " not found!" << std::endl;
	return NULL;
}

