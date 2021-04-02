#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_map>
#include <map>
#include "perf.h"
//http://interactivepython.org/courselib/static/pythonds/Trees/BinaryHeapImplementation.html
//
using namespace std;

int binarySearch(int arr[], int l, int r, int x){
	if (r >= l) {
		int mid = l + (r - l) / 2;
		if (arr[mid] == x)
			return mid;
		if (arr[mid] > x)
			return binarySearch(arr, l, mid - 1, x);
		return binarySearch(arr, mid + 1, r, x);
	}
	return -1;
}


template<typename T>
int binarySearch(T arr[], int start, int end, const T& element)
{
	if (end < start)
		return -1;

	int mid = (start + end) / 2;

	if (element == arr[mid])
	{
		return mid;
	}
	else if (element < arr[mid])
	{
		return binarySearch(arr, start, mid - 1, element);
	}
	else
	{
		return binarySearch(arr, mid + 1, end, element);
	}
}

template<>
int binarySearch<int>(int arr[], int start, int end, const int& element)
{
	if (end < start)
		return -1;

	int mid = (start + end) / 2;

	if (element == arr[mid])
	{
		return mid;
	}
	else if (element < arr[mid])
	{
		return binarySearch(arr, start, mid - 1, element);
	}
	else
	{
		return binarySearch(arr, mid + 1, end, element);
	}
}

template <typename Time = std::chrono::nanoseconds>
uint64_t T_STD_sorted_vector_std_bseach() {
	auto data = getData(MAX_SIZE);
	auto sortedData = data;
	std::sort(sortedData.begin(), sortedData.end());
	
	std::vector<Time> Timer(MAX_SIZE);
	for (size_t i = 0; i < MAX_SIZE; ++i) {
		auto start = Clock::now();
		//std::find(sortedData.begin(), sortedData.end(), data[i]);
		std::binary_search(sortedData.begin(), sortedData.end(), data[i]);
		auto time = std::chrono::duration_cast<Time>(Clock::now() - start);
		Timer[i] = time;
	}
	return average<Time>(Timer);
}

template <typename Time = std::chrono::nanoseconds>
uint64_t T_STD_sorted_vector_my_bseach() {
	auto data = getData(MAX_SIZE);
	auto sortedData = data;
	std::sort(sortedData.begin(), sortedData.end());

	std::vector<Time> Timer(MAX_SIZE);
	for (size_t i = 0; i < MAX_SIZE; ++i) {
		auto start = Clock::now();
		//std::find(sortedData.begin(), sortedData.end(), data[i]);
		binarySearch(sortedData.data(),0, sortedData.size()-1 , data[i]);
		auto time = std::chrono::duration_cast<Time>(Clock::now() - start);
		Timer[i] = time;
	}
	return average<Time>(Timer);
}

template <typename Time = std::chrono::nanoseconds>
uint64_t T_STD_unordered_map() {
	auto data = getData(MAX_SIZE);
	std::unordered_map<uint64_t, uint64_t> table;
	for (const auto& item : data){
		table.emplace(item,item);
	}

	std::vector<Time> Timer(MAX_SIZE);
	for (size_t i = 0; i < MAX_SIZE; ++i) {
		auto start = Clock::now();
		table.find(data[i]);
		auto time = std::chrono::duration_cast<Time>(Clock::now() - start);
		Timer[i] = time;
	}
	return average<Time>(Timer);
}

template <typename Time = std::chrono::nanoseconds>
uint64_t T_STD_map() {
	auto data = getData(MAX_SIZE);
	std::map<uint64_t, uint64_t> table;
	for (const auto& item : data) {
		table.emplace(item, item);
	}

	std::vector<Time> Timer(MAX_SIZE);
	for (size_t i = 0; i < MAX_SIZE; ++i) {
		auto start = Clock::now();
		table.find(data[i]);
		auto time = std::chrono::duration_cast<Time>(Clock::now() - start);
		Timer[i] = time;
	}
	return average<Time>(Timer);
}

void TestHashTablePerformance() {
	std::cout << " ------------------------------------------------------------------" << std::endl;
	std::cout << " T_STD_map                       : " << T_STD_map<std::chrono::nanoseconds>() << " nano" << std::endl;
	std::cout << " T_STD_unordered_map             : " << T_STD_unordered_map<std::chrono::nanoseconds>() <<" nano"<< std::endl;
	std::cout << " T_STD_sorted_vector_std_bseach  : " << T_STD_sorted_vector_std_bseach<std::chrono::nanoseconds>() << " nano" << std::endl;
	std::cout << " T_STD_sorted_vector_my_bseach   : " << T_STD_sorted_vector_my_bseach<std::chrono::nanoseconds>() << " nano" << std::endl;
}

