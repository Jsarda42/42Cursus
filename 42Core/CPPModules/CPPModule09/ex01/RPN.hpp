#pragma once
#include <stack>
#include <iostream>

class RPN {
	
	private:
		std::stack<int> stack_;
		std::string expression_;

	public:
		RPN(void);
		RPN& operator=(const RPN& rhs);
		RPN(const RPN& cpy);
		~RPN(void);

		void evaluateExpression(const std::string &expression);
};
