// C++ program to multiply two numbers represented
// as strings.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

std::string resultInString(const std::vector<int>& vecResult)
{
	// ignore '0's from the right
	int i = vecResult.size() - 1;
	while (i >= 0 && vecResult[i] == 0)
		i--;

	// If all were '0's - means either both or
	// one of num1 or num2 were '0'
	if (i == -1)
		return "0";

	// generate the result string
	string s = "";
	while (i >= 0)
		s += std::to_string(vecResult[i--]);
	return s;
}

// Multiplies str1 and str2, and prints result.
string multiply(string num1, string num2)
{
	int szNum1 = num1.size();
	int szNum2 = num2.size();
	if (szNum1 == 0 || szNum2 == 0)
		return "0";

	// will keep the result number in vector  in reverse order
	vector<int> result(szNum1 + szNum2, 0);

	// Below two indexes are used to find positions in result. 
	int outerShift = 0;
	int innerShift = 0;

	// Go from right to left in num1
	for (int multiplicandIndex = szNum1 - 1; multiplicandIndex >= 0; multiplicandIndex--)
	{
		int carry = 0;
		int multiplicand = num1[multiplicandIndex] - '0';

		// To shift position to left after every multiplication of a digit in num2
		innerShift = 0;

		// Go from right to left in num2             
		for (int multiplierIndex = szNum2 - 1; multiplierIndex >= 0; multiplierIndex--)
		{
			// Take current digit of second number
			int multiplier = num2[multiplierIndex] - '0';

			// Multiply with current digit of first number and add result to previously stored result at current position. 
			int sum = multiplier * multiplicand + result[outerShift + innerShift] + carry;

			// Carry for next iteration
			carry = sum / 10;

			// Store result
			result[outerShift + innerShift] = sum % 10;

			innerShift++;
		}

		// store carry in next cell
		if (carry > 0)
			result[outerShift + innerShift] += carry;

		// To shift position to left after every
		// multiplication of a digit in num1.
		outerShift++;
	}

	return resultInString(result);
}

// Driver code
int bigmultiply()
{
	string str1 = "1235421415454545454545454544";
	string str2 = "1714546546546545454544548544544545";
	cout << multiply(str1, str2);
	return 0;
}