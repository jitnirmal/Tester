#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
/// <summary>
/// Quick sort divides the input array into two partitions, which are the left partition and the right partition.
/// pivot is picked up with intention, all items that are lower than the pivot will be moved to the left sublist, and the rest will be in the right sublist
/// First item is picked to be pivot...After running the partition process, we will ensure that the pivot is in the correct position in the array. 
/// Quick sort is similar to merge sort in dividing an input array into two sublists, the time complexity of quick sort is O(N • log N) for the best case scenario
/// In the worst case scenario, we may pick the lowest or the greatest element as a pivot so that we have to iterate through all elements. In this case, the time complexity will be O(N2).
/// </summary>



auto print = [](int arr[], int length, int pivot, int low, int high) {
	std::cout <<"p="<<pivot<< ",l="<<low << ",h="<<high<<", arr=";
	for(unsigned int i = 0; i < length; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
};

int Partition( int arr[], int startIndex, int endIndex)
{
	int pivot = arr[startIndex];
	int swapIndex = startIndex;
	// swapIndex always holds last index of element smaller than pivot
	//   a. in upper loop it helps to swap any element greater than pivot
	//   b. finally pivot which is first index is swapped with the last index number < pivot..
	for (int i = startIndex + 1; i <= endIndex; ++i){
		if (arr[i] < pivot)	{
			++swapIndex;
			if (i != swapIndex){ // check to avoid self swap
				swap(arr[i], arr[swapIndex]);
			}
		}
	}
//	print(arr, endIndex- startIndex+1,pivot, startIndex, endIndex);
	swap(arr[startIndex], arr[swapIndex]);
//	print(arr, endIndex - startIndex + 1, pivot, startIndex, endIndex);
	return swapIndex;
}

void QuickSort(	int arr[],	int startIndex,	int endIndex)
{
	if (startIndex < endIndex)
	{
		//returned pivot is on the correct position..
		int pivotIndex = Partition(arr, startIndex, endIndex); 
		QuickSort(arr, startIndex, pivotIndex - 1);
		QuickSort(arr, pivotIndex + 1, endIndex);
	}
}

void testQuickSort()
{
	int arr[] = { 15,12,4,23,5,3,11,45 };
	int high = (sizeof(arr) / sizeof(int)) - 1;
	QuickSort(arr, 0, high);
}


/// <summary>
/// /////////////////////////////////////////////////////////////////////////////
/// </summary>




void quickSort(int arr[], int low, int high) {
	if (arr == nullptr )
		return;

	if (low >= high)
		return;

	// pick the pivot
	int middle = low + (high - low) / 2;
	int pivot = arr[middle];

	// make left < pivot and right > pivot
	int i = low, j = high;
	while (i <= j) {
		while (arr[i] < pivot) { i++;}

		while (arr[j] > pivot) { j--;}

		if (i <= j) { swap(arr[i],arr[j]);  i++; j--;	}

		print(arr,7, pivot,i,j);
	}

	// recursively sort two sub parts
	if (low < j)
		quickSort(arr, low, j);

	if (high > i)
		quickSort(arr, i, high);
}

