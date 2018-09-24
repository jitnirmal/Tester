#include <iostream>
#include <cmath>
using namespace std;

long long convertDecimalToBinary(int);
int convertBinaryToDecimal(long long);

int checkPrimeNumber(int n)
{
	bool flag = false;
	for (int i = 2; i <= n / 2; ++i)
	{
		if (n%i == 0)
		{
			flag = true;
			break;
		}
	}
	return flag;
}

long long convertDecimalToBinaryRS(unsigned int num)
{
	long long binaryNumber = 0;
	unsigned int mask = 32768;   //mask = [1000 0000 0000 0000]
	unsigned int current_bit = 0;

	while (mask > 0)
	{
		current_bit = num & mask;
		mask = mask >> 1;  // Right Shift
		binaryNumber += remainder * i;
		i *= 10;
	}
	return binaryNumber;
}

long long convertDecimalToBinary(int n)
{
	long long binaryNumber = 0;
	int remainder, i = 1, step = 1;

	while (n != 0)
	{
		remainder = n % 2;
		cout << "Step " << step++ << ": " << n << "/2, Remainder = " << remainder << ", Quotient = " << n / 2 << endl;
		n /= 2;
		binaryNumber += remainder * i;
		i *= 10;
	}
	return binaryNumber;
}

int convertBinaryToDecimal(long long n)
{
	int decimalNumber = 0, i = 0, remainder, step = 1;
	while (n != 0)
	{
		remainder = n % 10;
		cout << "Step " << step++ << ": " << n << "/10, Remainder = " << remainder << ", Quotient = " << n / 10 << endl;
		n /= 10;
		decimalNumber += remainder * pow(2, i);
		++i;
	}
	return decimalNumber;
}

long long convertOctalToBinary(int octalNumber)
{
	int decimalNumber = 0, i = 0;
	long long binaryNumber = 0;

	while (octalNumber != 0)
	{
		decimalNumber += (octalNumber % 10) * pow(8, i);
		++i;
		octalNumber /= 10;
	}

	i = 1;

	while (decimalNumber != 0)
	{
		binaryNumber += (decimalNumber % 2) * i;
		decimalNumber /= 2;
		i *= 10;
	}

	return binaryNumber;
}

int convertBinarytoOctal(long long binaryNumber)
{
	int octalNumber = 0, decimalNumber = 0, i = 0;

	while (binaryNumber != 0)
	{
		decimalNumber += (binaryNumber % 10) * pow(2, i);
		++i;
		binaryNumber /= 10;
	}

	i = 1;

	while (decimalNumber != 0)
	{
		octalNumber += (decimalNumber % 8) * i;
		decimalNumber /= 8;
		i *= 10;
	}

	return octalNumber;
}

int longestSequence(int decimalNum)
{
	auto remainder{ 1u };
	auto max_zero_count{ 0u };
	auto zero_count{ 0u };
	auto prev_zero{ false };
	auto start{ false };

	while (decimalNum != 0)
	{
		remainder = decimalNum % 2;
		decimalNum /= 2;

		if (remainder == 1)
			start = true;

		if (start)
		{
			if (remainder == 0)
			{
				++zero_count;
				prev_zero = true;
			}
			else if (remainder == 1 && prev_zero == true)
			{
				if (max_zero_count < zero_count)
					max_zero_count = zero_count;

				prev_zero = false;
				zero_count = 0;
			}
		}
	}
	return max_zero_count;
}


void testConversions()
{
	int n = 37;
	long long binaryNumber;
	int decimal;

	binaryNumber = convertDecimalToBinary(n);
	cout << n << " in decimal = " << binaryNumber << " in binary" << endl;
	std::cout << "-------------------------------------------------------------" << std::endl;
	decimal = convertBinaryToDecimal(binaryNumber);
	cout << n << " in decimal = " << decimal << " in decimal" << endl;
}
