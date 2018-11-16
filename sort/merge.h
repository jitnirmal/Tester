#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

/// <summary>
/// we need tempArray to store the sorted array as a result of the two sorted sublists being merged. 
/// It will rearrange the array by merging these two sublists. After this is completed, put all of 
/// the elements of the tempArray in the correct order. This will copy the temporary array into the original array.
/// </summary>
void Merge(	int arr[], 	int startIndex,	int middleIndex, int endIndex)
{
//	cout << "s : " << startIndex << " ,m : "<<middleIndex << " ,e : "<<endIndex << endl;
	int totalElements = endIndex - startIndex + 1;
	int* tempArray = new int[totalElements]; // Temporary array to store merged array

	int leftIndex = startIndex;
	int rightIndex = middleIndex + 1;
	int mergedIndex = 0;

	while (leftIndex <= middleIndex && rightIndex <= endIndex) // Merge the two subarrays
	{
		if (arr[leftIndex] <= arr[rightIndex])
		{
			tempArray[mergedIndex] = arr[leftIndex];
			++leftIndex;
		}
		else
		{
			tempArray[mergedIndex] = arr[rightIndex];
			++rightIndex;
		}
		++mergedIndex;
	}

	while (leftIndex <= middleIndex) // anything left .. copy it
	{
		tempArray[mergedIndex] = arr[leftIndex];
		++leftIndex;
		++mergedIndex;
	}

	while (rightIndex <= endIndex) // anything left .. copy it
	{
		tempArray[mergedIndex] = arr[rightIndex];
		++rightIndex;
		++mergedIndex;
	}

	
	for (int i = 0; i < totalElements; ++i) // Now, the merged array has been sorted..copy the elements to the original array
	{
		arr[startIndex + i] = tempArray[i];
	}

	delete[] tempArray;
	return;
}

void MergeSort(	int arr[],	int startIndex,	int endIndex)
{
	if (startIndex < endIndex)
	{
		int middleIndex = (startIndex + endIndex) / 2;
		MergeSort(arr, startIndex, middleIndex); // Sort left  and right subarray
		MergeSort(arr, middleIndex + 1, endIndex);
		Merge(arr, startIndex, middleIndex, endIndex);
	}

	return;
}


void TestMergeSort() {
	
	std::vector<int> arr = { 7, 1, 5, 9, 3, 6, 8, 2 };

	auto print = [&]() {
		for (const auto& i : arr )
			cout << i << " ";
		cout << endl;
	};
	
	print();
	MergeSort(arr.data(), 0, arr.size() - 1);
	print();
}