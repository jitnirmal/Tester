#pragma once

#include <iostream>
#include <vector>

//https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
int getSubArrayMaxSum(int arr[], int size)
{
	int maxSum = 0;
	int maxTillHere = 0;

	for (int i = 0; i < size; ++i)
	{
		maxTillHere += arr[i];
		
		if (maxTillHere < 0)
			maxTillHere = 0;

		if (maxSum < maxTillHere)
			maxSum = maxTillHere;
	}

	return maxSum;
}

void testSubArrayMaxSum()
{
	std::vector<int> v { -2, -3, 4, -1, -2, 1, 5, -3 };
	auto result = getSubArrayMaxSum(v.data(), v.size());
	std::cout << result << std::endl;
}

//XhBm6eo04qjl