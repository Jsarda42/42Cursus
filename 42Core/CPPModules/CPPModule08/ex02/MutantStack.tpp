#include "MutantStack.hpp"

template <typename T>
MutantStack<T>::MutantStack(void) {}

template <typename T>
MutantStack<T>::~MutantStack(void) {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &cpy) {
	*this = cpy;
}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack<T> &rhs) {
	if (this == &rhs)
		return *this;
	std::stack<T>::operator=(rhs);
	return *this;
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin(void) {
	return std::stack<T>::c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end(void) {
	return std::stack<T>::c.end();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin(void) const {
	return std::stack<T>::c.cbegin();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end(void) const {
	return std::stack<T>::c.cend();
}
