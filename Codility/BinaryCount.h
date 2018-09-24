#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <bitset>

int BinaryCountWithBitSet(unsigned int number)
{
	std::bitset<32> bitsTable(number);
	int count{ 0 };
	for (int i = 0; i < bitsTable.size(); ++i)
	{
		if (bitsTable[i] == 1)
		{
			++count;
		}
	}
	return count;
}

int BinaryCountWithShift(unsigned int number)
{
	int count{ 0 };
	while(number != 0)
	{
		if ((number & 1) != 0)
			++count;
		number >>= 1;
	}
	return count;
}

int solution(string S) {
	int number = atoi(S.c_str());
	int count{ 0 };
	while (number != 0)
	{
		if (number % 2 == 0)
		{
			//right shift
			number >>= 1;
		}
		else
		{
			number ^= 1;
		}
		++count;
	}
	return count;
}

int solution2(string S) {
	//int number = atoi(S.c_str());
	int count{ 0 };
	while (atoi(S.c_str()) != 0)
	{
		int index = S.length() - 1;
		if (S[index] == '0')
		{
			//right shift
			S.erase(index, 1);
		}
		else
		{
			S[index] = '0';
		}
		++count;
	}
	return count;
}

int solution5(string &S) {
	
	while (S.length() >0 )
	{
		if (S[0] == '0')
			S.erase(0, 1);
		else
			break;
	}
	// write your code in C++14 (g++ 6.2.0)
	int count{ 0 };
	while (S == "0")
	{
		int index = S.length() - 1;
		if (S[index] == '0')
		{
			S.erase(index, 1);
		}
		else
		{
			S[index] = '0';
		}
		++count;
	}
	return count;
}


int solution6(string &S) {
	// write your code in C++14 (g++ 6.2.0)
	int count{ 0 };

	//remove the leading 0, i.e. 000110 --> 110

	while (S.length() > 0)
	{
		if (S[0] == '0')
			S.erase(0, 1);
		else
			break;
	}

	while (S.length() > 0 && S != "0" )
	{
		int index = S.length() - 1;
		if (S[index] == '0')
		{
			S.erase(index, 1);
		}
		else
		{
			S[index] = '0';
		}
		++count;
	}
	return count;
}

void Merge(const char *s1, const char *s2, char *output)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		*output++ = *s1++;
		*output++ = *s2++;
	}
	while (*s1 != '\0')//this part not reqd if the length is same
		*output++ = *s1++;
	while (*s2 != '\0')//this part not reqd. if the length is same
		*output++ = *s2++;
	*output = '\0';
}

// Complete the numberOfPairs function below.
int numberOfPairs(vector<int> a, long k) {
	std::unordered_set<int> numberTable;
	for (const auto& it : a)
	{
		numberTable.insert(it);
	}
	int count{ 0 };
	for (const auto& it : a)
	{
		auto search = k - it;
		if (it != search)
		{
			auto iter = numberTable.find(search);
			if (iter != numberTable.end())
			{
				++count;
				numberTable.erase(iter);
				numberTable.erase(numberTable.find(it));
			}
		}
	}
	return count;
}

#include <vector>
#include <unordered_map>
#include <utility>

std::vector<std::pair<int, int>> FindPairsForSum(
	const std::vector<int>& data, const int& sum)
{
	std::unordered_map<int, size_t> umap;
	std::vector<std::pair<int, int>> result;
	for (size_t i = 0; i < data.size(); ++i)
	{
		if (0 < umap.count(sum - data[i]))
		{
			size_t j = umap[sum - data[i]];
			result.push_back({ data[i], data[j] });
		}
		else
		{
			umap[data[i]] = i;
		}
	}

	return result;
}

void  TestBinaryCount()
{
//	std::vector<int> A{6,6,3,9,3,5,1};
//	int number = 12;
	
//	std::vector<int> A{ 1,3,46,1,3,9 };
//	int number = 47;
	
	std::vector<int> A{ 6,12,3,9,3,5,1 };
	int number = 12;

	
	auto count = FindPairsForSum(A,number);

	int x;
}