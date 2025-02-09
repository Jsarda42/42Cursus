#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
int easyfind(T &container, int value) {
	typename T::iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw std::exception();
	return *it;
}
