#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <list>
#include <deque>
#include <functional>
#include <vector>
#include "perf.h"
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
//***********************************Tests*****************************//
template <typename Time = std::chrono::nanoseconds>
uint64_t T_QSort() {
	auto data = getData(MAX_SIZE);
	std::vector<Time> Timer(ITERATIONs);
	for (size_t i = 0; i < ITERATIONs; ++i) {
		auto vdata = data;
		auto start = Clock::now();
		QuickSort(vdata.data(), 0, vdata.size() - 1);
		auto time = std::chrono::duration_cast<Time>(Clock::now() - start);
		Timer[i] = time;
	}
	return average<Time>(Timer);
}

template <typename Time = std::chrono::nanoseconds>
uint64_t T_STD_Sort() {
	auto data = getData(MAX_SIZE);
	std::vector<Time> Timer(ITERATIONs);
	for (size_t i = 0; i < ITERATIONs; ++i) {
		auto vdata = data;
		auto start = Clock::now();
		std::sort(vdata.begin(), vdata.end());
		auto time = std::chrono::duration_cast<Time>(Clock::now() - start);
		Timer[i] = time;
	}
	return average<Time>(Timer);
}

//to sort a list we should use list::sort, std::sort requires random-access iterators 
// (supporting jumps of arbitrary size)whereas list iterators can only go forwards or 
// backwards by one link at a time.
template <typename Time = std::chrono::nanoseconds>
uint64_t T_STD_deque_Sort() {
	auto data = getData(MAX_SIZE);
	
	std::vector<Time> Timer(ITERATIONs);
	for (size_t i = 0; i < ITERATIONs; ++i) {
		std::deque<int> dq(data.begin(), data.end());
		auto start = Clock::now();
		std::sort(dt.begin(), dq.end());
		auto time = std::chrono::duration_cast<Time>(Clock::now() - start);
		Timer[i] = time;
	}
	return average<Time>(Timer);
}

template <typename Time = std::chrono::nanoseconds>
uint64_t T_STD_list_Sort() {
	auto data = getData(MAX_SIZE);

	std::vector<Time> Timer(ITERATIONs);
	for (size_t i = 0; i < ITERATIONs; ++i) {
		std::list<int> lt(data.begin(), data.end());
		auto start = Clock::now();
		lt.sort();
		auto time = std::chrono::duration_cast<Time>(Clock::now() - start);
		Timer[i] = time;
	}
	return average<Time>(Timer);
}

void TestQSortPerformance() {
	std::cout << " ------------------------------------------------------------------" << std::endl;
	std::cout << " T_QSort                         : " << T_QSort<std::chrono::milliseconds>() << " milli"<<std::endl;
	std::cout << " T_STD_vector_Sort               : " << T_STD_Sort<std::chrono::milliseconds>()<< " milli"<< std::endl;
	std::cout << " T_STD_list_Sort                 : " << T_STD_list_Sort<std::chrono::milliseconds>() << " milli" << std::endl;
	std::cout << " T_STD_deque_Sort                : " << T_STD_list_Sort<std::chrono::milliseconds>() << " milli" << std::endl;
}
