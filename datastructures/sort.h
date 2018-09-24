#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>


template<class ForwardIt, class Compare>
ForwardIt min_element(ForwardIt first, ForwardIt last,
	Compare comp)
{
	if (first == last) return last;
	ForwardIt smallest = first;
	++first;
	for (; first != last; ++first) {
		if (comp(*first, *smallest)) {
			smallest = first;
		}
	}
	return smallest;
}

template<class FwdIt, class Compare = std::less<>>
void selection_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
	for (auto it = first; it != last; ++it) {
		auto const selection = std::min_element(it, last, cmp);
		std::iter_swap(selection, it);
		//assert(std::is_sorted(first, std::next(it), cmp));
	}
}


template<typename Iterator>
void bubble_sort(Iterator begin, Iterator end){
	while (true) {
		bool c = false; // changed?
		for (auto iter = begin; iter < end ; ++iter) {
			if (*iter > *(iter + 1)) {
				std::iter_swap(iter, iter + 1);
				c = true;
			}
		}
	}
}

void testBubbleSort()
{
	std::cout << "Bubble Sort" << std::endl;
	std::array<int,6> arr = { 43, 21, 26, 38, 17, 30 };
	
	std::cout << std::endl;
	bubble_sort(arr.begin(),arr.end());
	
	std::cout << "Sorted array : ";
	for (auto i = 0u; i < arr.size(); ++i)
		std::cout << arr[i] << " ";
	
	std::cout << std::endl;
}



class IncreasingNumber {
public:
	int operator()()
	{
		return ++counter;
	}
private:
	int counter = { 0 };
};


void Test1()
{
	constexpr auto MAX_ELEMENTS{ 100 };
	std::vector<int> vi(MAX_ELEMENTS);
	std::generate(vi.begin(), vi.end(), IncreasingNumber());
	std::transform(vi.begin(), vi.end(), vi.begin(), [](const auto& num) {return num * num; });
	std::for_each(vi.begin(), vi.end(), [](const auto& num) {std::cout << num << " "; });
}

void Test2()
{
	constexpr auto MAX_ELEMENTS{ 100 };
	std::vector<int> vi;
	std::generate_n(std::back_inserter(vi), MAX_ELEMENTS, [n = 0]() mutable { ++n; return n * n; });
	std::for_each(vi.begin(), vi.end(), [](const auto& num) {std::cout << num << " "; });
}

void TestUtils()
{
	Test2();
}