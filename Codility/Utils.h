#pragma once

#include<iostream>
#include<stack>
#include<string>
using namespace std;
#include <bitset>
#include <vector>
#include <list>
#include <algorithm>

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