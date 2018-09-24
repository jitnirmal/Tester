#pragma once
#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;
//https://github.com/indiesquidge/javascript-challenges/tree/master/stack-machine-calculator

#include <sstream>

bool isNumeric(const string& str) {

	for (const auto& c : str)
	{
		if (std::isdigit(c) == false)
			return false;
	}
	return true;
}
void operate(std::stack<int>& stack, int multiplier)
{
	auto result = stack.top();
	stack.pop();

	result = result + (multiplier * stack.top());
	stack.pop();

	stack.push(result);
}

int solution(string &S) {

	stack<int> stack;
	std::istringstream ss(S);
	std::string token;

	std::vector<std::string> words;

	while (std::getline(ss, token, ' ')) {
		words.push_back(token);
	}

	for (auto& str : words) {
		if (isNumeric(str)) {
			stack.push(std::atoi(str.c_str()));
		}
		else if (str == "DUP") {
			stack.push(stack.top());

		}
		else if (str == "POP") {
			stack.pop();
		}
		else if (str == "+") {

			if (stack.size() <= 1)
				return -1;
			operate(stack, 1);
		}
		else if (str == "-") {

			if (stack.size() <= 1)
				return -1;

			operate(stack, -1);
		}
	}
	return stack.top();
}


int main() {

	std::string str1("13 DUP 4 POP 5 DUP + DUP + -");
	std::string str2("3 DUP 5 - -");
	std::cout << solution(str1) << "\n";
	std::cout << solution(str2) << "\n";
	return 0;
}