#include <iostream>
#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class AMateria;
class Cure;
class Ice;

class MateriaSource : public IMateriaSource {

	private:

		AMateria* learnedMateria_[4];

	public:

		MateriaSource(void);
		MateriaSource(const MateriaSource& cpy);
		MateriaSource& operator=(const MateriaSource& rhs);
		~MateriaSource(void);

		void learnMateria(AMateria*);
		AMateria* createMateria(const std::string& type);
};
