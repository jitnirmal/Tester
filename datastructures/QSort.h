#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>

auto print = [](int arr[], int length, int pivot, int low, int high) {
	std::cout <<"pivot="<<pivot<< ",low="<<low << ",high="<<high<<", arr=";
	for(unsigned int i = 0; i < length; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
};

void swap(int* src, int* dest)
{
	int temp = *src;
	*src = *dest;
	*dest = temp;
}

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

		if (i <= j) { swap(&arr[i],&arr[j]);  i++; j--;	}

		print(arr,7, pivot,i,j);
	}

	// recursively sort two sub parts
	if (low < j)
		quickSort(arr, low, j);

	if (high > i)
		quickSort(arr, i, high);
}

void testSort()
{
	int arr[] = {15,12,4,23,5,3,11,45};
	int high = (sizeof(arr) / sizeof(int)) -1;
	quickSort(arr,0,high);
}