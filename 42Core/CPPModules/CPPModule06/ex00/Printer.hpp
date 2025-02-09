#pragma once
#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>

class Printer {

	private:
		Printer(void);
		~Printer(void);
		Printer& operator=(const Printer& rhs);
		Printer(const Printer& cpy);

	public:
		static void printChar(const char c);
		static void printInt(const int i);
		static void printFloat(const float f);
		static void printDouble(const double d);
		static void printNaN(void);
		static void printOverflow(void);
};
