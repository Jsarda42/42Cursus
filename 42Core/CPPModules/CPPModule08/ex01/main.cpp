#include "Span.hpp"
#include <iostream>
#include <vector>

int main(void) {
	std::cout << "Span tests:------" << std::endl;
	std::cout << "Simple test:------" << std::endl;
{	
	Span span = Span(5);

	span.addNumber(5);
	span.addNumber(3);
	span.addNumber(17);
	span.addNumber(9);
	span.addNumber(11);

	std::cout << "Shortest span:" << span.shortestSpan() << std::endl;

	std::cout << "Longest span: " << span.longestSpan() << std::endl;
}
	std::cout << "Test with 10000:------" << std::endl;
{
	Span span = Span(10000);

	for (int i = 0; i < 10000; i++)
		span.addNumber(i);
	
	std::cout << "Shortest span: " << span.shortestSpan() << std::endl;

	std::cout << "Longest span: " << span.longestSpan() << std::endl;

	try {
		span.addNumber(42);
	} 
	catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}
	std::cout << "Test with 1 element:------" << std::endl;
{
	Span span = Span(1);

	try {
		span.shortestSpan();
	} 
	catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}
	std::cout << "Test with multiple numbers:------" << std::endl;
{
	Span span = Span(5);

	std::vector<int> v;
	v.push_back(5);
	v.push_back(3);
	v.push_back(17);
	v.push_back(9);
	v.push_back(11);

	span.addMultipleNumbers(v.begin(), v.end());

	std::cout << "Shortest span: " << span.shortestSpan() << std::endl;

	std::cout << "Longest span: " << span.longestSpan() << std::endl;

	try {
		span.addMultipleNumbers(v.begin(), v.end());
	} 
	catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}
	return 0;
}
