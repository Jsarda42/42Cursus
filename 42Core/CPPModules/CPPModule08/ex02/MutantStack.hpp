// Il est temps de passer aux choses sérieuses. Créons une classe mutante.

// Le container std::stack est top. Malheureusement, c’est l’un des seuls de la STL à
// ne PAS être itérable. Trop nul.
// Mais d’où devrions-nous tolérer cela ? Surtout quand on peut s’octroyer le droit de
// charcuter la stack originale pour ajouter cette caractéristique manquante.

// Afin de réparer cette injustice, vous allez rendre le container std::stack itérable.

// Implémentez une classe MutantStack. Elle sera implémentée en termes de la
// std::stack. Elle offrira toutes ses fonctions membres avec en plus des itérateurs.
// Bien entendu, implémentez et rendez vos propres tests afin de démontrer que tout
// marche comme attendu.

#pragma once
#include <iostream>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
	private:

	public:
		MutantStack(void);
		~MutantStack(void);
		MutantStack(const MutantStack &cpy);
		MutantStack<T> &operator=(const MutantStack<T> &rhs);

		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;

		iterator begin(void);
		iterator end(void);
		const_iterator begin(void) const;
		const_iterator end(void) const;
};

#include "MutantStack.tpp"
