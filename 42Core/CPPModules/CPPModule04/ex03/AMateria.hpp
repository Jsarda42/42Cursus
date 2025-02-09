#pragma once
#include <iostream>

class ICharacter;

class AMateria {

	protected:

		std::string type_;

	public:

	AMateria( void );
	AMateria( const std::string& type );
	AMateria( const AMateria& cpy );
	AMateria& operator=( const AMateria& rhs );
	virtual ~AMateria( void );

	std::string const & getType() const;
	virtual AMateria* clone() const = 0;
	virtual void use(ICharacter& target) = 0;
};
