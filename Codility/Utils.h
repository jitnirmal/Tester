#pragma once

#include<iostream>
#include<stack>
#include<string>
using namespace std;
#include <bitset>
#include <vector>
#include <list>
#include <algorithm>

#define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))
#define NTOHS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

#define HTONL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))

#define NTOHL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))

void TestBitManipulation()
{
	//Testing bits : The following code tests to see whether bit 3 is set in the timer status register using the & operator:
	int x = 01;
	if (x & 0x08){}

	//Setting bits : To set bit 4, the | operator is used as shown in the following code :
	x |= 0x10;

	// clearning bits : uses the & and ~ operators as follows:
	x &= ~(0x04);

	//Shifting bits
	// use unsigned intergers, most significant bit to be repeated when the variable is signed.
	unsigned int bitCount = 200;

	// right shift by 1
	bitCount >>= 1;

	// left shift by 3
	bitCount <<= 3;


	struct
	{
		uint8_t  bit0 : 1;
		uint8_t  bit1 : 1;
		uint8_t  bit2 : 1;
		uint8_t  bit3 : 1;
		uint8_t  nibble : 4;
	} foo;

	//Bits within a bitfield can be individually set, tested, cleared, and toggled without affecting the state of the other bits outside the bitfield.
	if (foo.bit0)
	{
		/* Do other stuff. */
	}
	if (foo.nibble == 0x03)
	{
		/* Do other stuff. */
	}

	//To set a bit using a bitfield, use this code:
	foo.bit1 = 1;
	foo.nibble = 0xC;
	foo.bit3 = ~foo.bit3;

}


// -----------------------------------------------------------------------------------------------------------------------------------------------------
//			LITTLE BIG INDIAN
// -----------------------------------------------------------------------------------------------------------------------------------------------------

int is_big_endian(void)
{
	union {
		uint32_t i;
		char c[4];
	} e = { 0x01000000 };

	return e.c[0];
}






// -----------------------------------------------------------------------------------------------------------------------------------------------------
//			BIG SORT ALGO
// -----------------------------------------------------------------------------------------------------------------------------------------------------

/// <summary>
/// check is called twicely by sort
/// </summary>
bool check(const string& a, const string& b) 
{
	return a.length() == b.length() ? a < b : a.length() < b.length();
}

void testBigSort() {
	std::vector<std::string> v{	"6","31415926535897932384626433832795",	"1","3","10","3","5"};
	std::sort(v.begin(), v.end(), check);

	for (const auto& item : v){
		std::cout << item << ", ";
	}
	std::cout << std::endl;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// divide without using division operator
/// https://www.techiedelight.com/perform-division-two-numbers-without-using-division-operator/
/// 

int divide(int x, int y) {
	int quotient = 0;
	// loop till dividend x is more than the divisor y
	while (x >= y)
	{
		x = x - y;		// perform reduction on dividend
		quotient++;		// increase quotient by 1
	}
	int remainder = x;
}
// -----------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------

/// <summary>
/// Mean and median
/// </summary>
/// 
/// // Function for calculating mean 
double findMean(int a[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += a[i];
	return (double)sum / (double)n;
}

// Function for calculating median 
double findMedian(int a[], int n)
{
	// First we sort the array 
	std::sort(a, a + n);

	// check for even case 
	if (n % 2 != 0)
		return (double)a[n / 2];

	return (double)(a[(n - 1) / 2] + a[n / 2]) / 2.0;
}




//A binary gap within a positive integer N is any maximal sequence of consecutive zeros 
//that is surrounded by ones at both ends in the binary representation of N.

int BinaryGap(unsigned int N)
{
	std::bitset<32> bitsTable(N);
	int currentZeroCount{ 0 };
	int maxCount{ 0 };
	bool startCounter{ false };
	bool prevZero{false};
	// 00000100001
	for (int i = bitsTable.size()-1; i >= 0; --i)
	{
		//std::cout << bitsTable[i];
		if (startCounter == false && bitsTable[i] == 1)
		{
			startCounter = true;
		}
		if (startCounter == true)
		{
			if (bitsTable[i] == 0)
			{
				++currentZeroCount;
				prevZero = true;
			}
			else if (bitsTable[i] == 1 && prevZero == true)
			{
				if (maxCount < currentZeroCount)
				{
					maxCount = currentZeroCount;
				}
				currentZeroCount = 0;
				prevZero = false;
			}
		}
	}
	std::cout << std::endl;
	return maxCount;
}

std::vector<int> RotateArray(std::vector<int> &A, int K) {
	
	std::list<int> lt{ std::begin(A), std::end(A) };
	for (unsigned int i = 0; i < K; ++i)
	{
		lt.push_front(lt.back());
		lt.pop_back();
	}
	return std::vector<int>{ std::begin(lt), std::end(lt) };
}
void TestRotateArray()
{
	std::vector<int> A{3, 8, 9, 7, 6};
	auto result = RotateArray(A,4);
}
/**************************************************************************************************/
//
int FindOddinPairedArray(vector<int> &A) {
	if (A.size() == 1)
		return A[0];
	std::sort(A.begin(), A.end());

	int number{ 0 };



	for (unsigned int i = 0; i < A.size(); i = i + 2)
	{
		if (i + 1 == A.size())
		{
			return A[i];
		}
		if (A[i] != A[i + 1])
		{
			return A[i];
		}
	}
	return number;
}

void TestFindOddinPairedArray()
{
	std::vector<int> A{ 9, 3, 9, 3, 9, 7, 9 };
	auto number = FindOddinPairedArray(A);
}

/***********************************************************************************************/

int findIndexSimple(string s) {
	auto begin = 0;
	auto  end = s.length() - 1;
	while (begin <= end) {
		if (s[begin] != '(') {
			++begin;
		}
		else if (s[end] != ')') {
			--end;
		}
		else {
			++begin;
			--end;
		}
	}
	return begin;
}

int findIndex(string str)
{
	int closingBracket = 0;
	int openingBracket = 0;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ')') {
			closingBracket++;
		}
	}

	for (int i = 0; i < str.length(); i++) {
		if (openingBracket == closingBracket) {
			return i;
		}
		
		if (str[i] == ')') {
			closingBracket--;
		}
		else if (str[i] == '(') {
			openingBracket++;
		}
	}
	return -1;
}


void TestUtils()
{
	//auto number = BinaryGap(561892);
	//TestRotateArray();
	//TestFindOddinPairedArray();
	string str = "(()))(()()())))";
	//string str = "()())";
	std::cout<<" : " << findIndexSimple(str) << std::endl;
}

//10001001001011100100
//10001001001011100100
//10001001001011100100
//0000000000001000100100101110010