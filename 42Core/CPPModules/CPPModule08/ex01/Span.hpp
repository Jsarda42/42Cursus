#pragma once

#include <iostream>
#include <vector>

class Span {
	private :
		unsigned int N_;
		std::vector<int> arr_;
		

	public :
		Span(void);
		Span(unsigned int N);
		Span(const Span &cpy);
		Span &operator=(const Span &rhs);
		~Span(void);

		void addNumber(int n);
		int shortestSpan(void);
		int longestSpan(void);
		void addMultipleNumbers(std::vector<int>::iterator begin, std::vector<int>::iterator end);
};
