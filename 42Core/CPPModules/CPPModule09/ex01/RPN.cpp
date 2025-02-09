#include "RPN.hpp"
#include <sstream>
#include <cstdlib>

RPN::RPN() {}

RPN& RPN::operator=(const RPN& rhs) {
	if (this != &rhs) {
		stack_ = rhs.stack_;
		expression_ = rhs.expression_;
	}
	return (*this);
}

RPN::RPN(const RPN& cpy) {
	stack_ = cpy.stack_;
	expression_ = cpy.expression_;
}

bool isSignExpression(std::string token) {
	if (token == "+" || token == "-" || token == "/" || token == "*")
		return true;
	return false;
}

void RPN::evaluateExpression(const std::string &expression) {
	if (expression.empty())
		throw std::runtime_error("Expression cannot be empty.");
	std::string token;
	std::istringstream tokens(expression);
	while (tokens >> token) {
		try {
			int number = std::atoi(token.c_str());
			if ((std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) && (number >= -10 && number <= 10))
					stack_.push(number);
			else if (token.size() == 1 && isSignExpression(token)) {
				 if (stack_.size() < 2)
					throw std::runtime_error("Invalid expression: Not enough operands for operator.");
				int a = stack_.top();
				stack_.pop();
				int b = stack_.top();
				stack_.pop();
				if (token == "-")
					stack_.push(b - a);
				else if (token == "+")
					stack_.push(a + b);
				else if (token == "*")
					stack_.push(a * b);
				else if (token == "/") {
					if (a == 0)
						throw std::runtime_error("Division by zero is not allowed.");
					stack_.push(b / a);
				}
			}
			else
				throw std::runtime_error("Invalid token: Only numbers between -10 and 10, and operators +, -, *, / are allowed.");
		}
		catch (std::exception &e){
			std::cerr << e.what();
			return ;
		}
	}
	if (stack_.size() != 1)
		throw std::runtime_error("Invalid expression: Too many operands or insufficient operators.");
	std::cout << "Result: " << stack_.top() << std::endl;
	stack_.pop();
}

RPN::~RPN() {}
