#pragma once

#include<iostream>
#include<stack>
#include<string>
using namespace std;
// Function to check whether two characters are opening 
// and closing of same type. 
bool ArePair(char opening, char closing)
{
	if (opening == '(' && closing == ')') return true;
	else if (opening == '{' && closing == '}') return true;
	else if (opening == '[' && closing == ']') return true;
	return false;
}
bool checkForBalancedParantheses(const string& exp)
{
	stack<char>  S;
	for (int i = 0; i<exp.length(); i++)
	{
		if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
			S.push(exp[i]);
		else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
		{
			if (S.empty() || !ArePair(S.top(), exp[i]))
				return false;
			else
				S.pop();
		}
	}
	return S.empty() ? true : false;
}

void testParanthesesBalanced()
{
	/*Code to test the function AreParanthesesBalanced*/
	string expression = "'[[]]['";
	if (checkForBalancedParantheses(expression))
		cout << "Balanced\n";
	else
		cout << "Not Balanced\n";
}