#pragma once
#include <stdexcept>

template <typename T>
class Array {
	private:
		T* elem_;
		unsigned int size_;

	public:
		Array(void);
		Array(unsigned int n);
		Array(const Array& cpy);
		const Array& operator=(const Array& rhs);
		T& operator[](unsigned int index);
		const T& operator[](unsigned int index) const;
		~Array(void);

		unsigned int size(void) const;
};

#include "Array.tpp"
