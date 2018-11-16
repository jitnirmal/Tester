#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
#include <list>

/// <summary>
/// 1) std::sort Sorts the elements in the range [first, last) in ascending order. The order of equal elements is not guaranteed to be preserved.
///		a.  Elements are compared using operator< or binary comparison function comp.
/// 2) std::stable_sort : Sorts the elements in the range [first, last) in ascending order. 
///			-- The order of equivalent elements is guaranteed to be preserved
/// 3) std::partial_sort : Rearranges elements such that the range [first, middle) contains the sorted middle - 
///			first smallest elements in the range [first, last). 
///			The order of equal elements is not guaranteed to be preserved.
///			The order of the remaining elements in the range[middle, last) is unspecified.
/// 4) nth_element partially sorts the range [first, last) in ascending order
///			-- you need to identify the top n elements without putting them in order (top 3rd, median etc)
/// 5) stable_partition :
/// /// </summary>

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

/// <summary>
/// ALthough it seems to be quite efficient but its not. Because erase function deletes
///  the elements and shifts all the elements in right by 1.So, it complexity will be O(n ^ 2).
/// </summary>
void removeAllMatchingElements_nonEfficient(std::vector<int> & vec, int elem)
{
	std::vector<int>::iterator it = vec.begin();
	while (it != vec.end())
	{
		if (*it == elem)
		{
			it = vec.erase(it);
		}
		else
			it++;
	}
}
/// <summary>
/// std::remove transforms the given range into a range with all the elements that compare not equal to 
/// given element shifted to the start of the container. So, actually dont remove the matched elements.
/// </summary>
/// 
void removeAllMatchingElements_Efficient(std::vector<int> & vec, int elem)
{
	vec.erase(std::remove(vec.begin(), vec.end(), elem), vec.end());
}


/*Generic function to find if an element of any type exists in list */
template <typename T>
bool contains(std::list<T> & listOfElements, const T & element)
{
	// Find the iterator if element in list
	auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
	//return if iterator points to end or not. It points to end then it means element
	// does not exists in list
	return it != listOfElements.end();
}



void TestUtils()
{
	Test2();
}