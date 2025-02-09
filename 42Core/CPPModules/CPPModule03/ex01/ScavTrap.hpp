#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {

	private:


	public:

		ScavTrap& operator=( ScavTrap& rhs );
		ScavTrap( ScavTrap& cpy );
		ScavTrap( void );
		ScavTrap( std::string name );
		~ScavTrap( void );
		void attack(const std::string& target);
		void guardGate();
};
