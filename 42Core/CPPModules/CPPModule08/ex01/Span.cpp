#include "Span.hpp"
#include <algorithm>
#include <stdexcept>
#include <limits>

Span::Span(void) : N_(0) {}

Span::Span(unsigned int N) : N_(N) {}

Span::Span(const Span &cpy) {
	*this = cpy;
}

Span &Span::operator=(const Span &rhs) {
	if (this == &rhs)
		return *this;
	N_ = rhs.N_;
	arr_ = rhs.arr_;
	return *this;
}

Span::~Span(void) {}

void Span::addNumber(int n) {
	if (arr_.size() == N_)
		throw std::out_of_range("Array is full");
	arr_.push_back(n);
}

int Span::shortestSpan(void) {
	if (arr_.empty() || arr_.size() == 1)
		throw std::out_of_range("Less than 2 elements in array");
	std::vector<int> tmp = arr_;
	std::sort(tmp.begin(), tmp.end());
	int min = std::numeric_limits<int>::max();
	for (size_t i = 0; i < tmp.size() - 1; i++) {
		if (tmp[i + 1] - tmp[i] < min)
			min = tmp[i + 1] - tmp[i];
	}
	return min;
}

int Span::longestSpan(void) {
	if (arr_.empty() || arr_.size() == 1)
		throw std::out_of_range("Less than 2 elements in array");
	std::vector<int>::iterator min = std::min_element(arr_.begin(), arr_.end());
	std::vector<int>::iterator max = std::max_element(arr_.begin(), arr_.end());
	return *max - *min;
}

void Span::addMultipleNumbers(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
	if (arr_.size() + std::distance(begin, end) > N_)
		throw std::out_of_range("Array is full");
	arr_.insert(arr_.end(), begin, end);
}
