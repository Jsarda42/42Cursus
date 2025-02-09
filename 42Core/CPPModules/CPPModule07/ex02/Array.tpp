#pragma once
#include "Array.hpp"

template <typename T>
Array<T>::Array(void) : elem_(NULL), size_(0){}

template <typename T>
Array<T>::Array(unsigned int n) : elem_(new T[n]), size_(n) {}

template <typename T>
Array<T>::Array(const Array& cpy) : elem_(new T[cpy.size_]), size_(cpy.size_){
	for (unsigned int i = 0; i < size_; i++) {
		elem_[i] = cpy.elem_[i];
	}
}

template <typename T>
const Array<T>& Array<T>::operator=(const Array& rhs) {
	if (this != &rhs) {
		delete [] elem_;

		size_ = rhs.size_;
		elem_ = new T[rhs.size_];
		for (unsigned int i = 0;i < rhs.size_; i++)
			elem_[i] = rhs.elem_[i];
	}
	return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index) {
	if (index >= size_)
		throw std::out_of_range("out of range");
	return elem_[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const {
	if (index >= size_)
		throw std::out_of_range("out of range");
	return elem_[index];
}

template <typename T>
unsigned int Array<T>::size(void) const {
	return size_;
}

template <typename T>
Array<T>::~Array(void) {
	delete [] elem_;
}
