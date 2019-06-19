#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
#include "perf.h"
//http://interactivepython.org/courselib/static/pythonds/Trees/BinaryHeapImplementation.html
//
using namespace std;



void countSort(int arr[], int n, int exp)
{
	int* output = new int[n]; // output array 
	int i, count[10] = { 0 };

	// Store count of occurrences in count[] 
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual 
	//  position of this digit in output[] 
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array 
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now 
	// contains sorted numbers according to current digit 
	for (i = 0; i < n; i++)
		arr[i] = output[i];

	delete[] output;
}

// The main function to that sorts arr[] of size n using  
// Radix Sort 
void radixsort(int arr[], int n)
{
	// Find the maximum number to know number of digits 
	auto result = std::max_element(arr, arr+n);

	// Do counting sort for every digit. Note that instead 
	// of passing digit number, exp is passed. exp is 10^i 
	// where i is current digit number 
	for (int exp = 1; *result / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}
void TestRadixSort() {
	
	std::vector<int> data{ 5, 7, 13, 8, 3, 9, 12, 10 };
	
	auto print = [&]() {
		for (const auto& item : data) {
			std::cout << item << " ";
		}
		std::cout << endl;
	};
	std::cout << "radix sort" << std::endl;
	print();
	radixsort(data.data(),data.size());
	print();
	
	
}

template <typename Time = std::chrono::nanoseconds>
uint64_t T_RedixSort() {
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

void TestRedixSortPerformance() {
	std::cout << " ------------------------------------------------------------------" << std::endl;
	std::cout << " T_RedixSort                     : " << T_RedixSort<std::chrono::milliseconds>() << " milli" << std::endl;
}
