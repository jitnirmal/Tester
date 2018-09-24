// C++ program to multiply two numbers represented
// as strings.

#include <iostream>
#include <vector>
#include <string>
using namespace std;


int nextNumber(int number)
{
	std::string strNum = std::to_string(number);
	for (int i = strNum.size() - 1; i > 0; --i)
	{
		if (strNum[i] > strNum[i - i])
		{
			std::swap(strNum[i], strNum[i - i]);
			break;
		}
	}
	return std::atoi(strNum.c_str());
}


// Driver code
int testNextNum()
{
	int number = 12345;
	auto result = nextNumber(number);
	return 0;
}

