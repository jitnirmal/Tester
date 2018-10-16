#pragma once
#include <unordered_map>
#include <random>
#include <map>
#include <iostream>
#include <iterator>
#include <set>

/// <summary>
/// An iterator is a class that abstracts the process of moving through a sequence.
/// Iterator categories
/// Input: read-only, one pass : istream_iterator, istreambuf_iterator,
///			-- you can dereference it for reading (once only for each value), and move it forward
/// Output: write-only, one pass : ostream_iterator, ostreambuf_iterator to write to ostream,
///			-- you can dereference it for writing (once only for each value) and move it forward.
/// Forward: multiple read/write : contains all the functionality of both the input iterator and the output
///				iterator, plus you can dereference an iterator location multiple times
///				-- you can only move forward
/// Bidirectional: all the functionality of the forward iterator, 
///				and in addition it can be moved backwards
/// Random-access :
///				--all the functionality of the bidirectional iterator
///				-- all the functionality of a pointer
///				-- indexing with operator[ ]
/// </summary>

template<class InputIt, class OutputIt>
OutputIt m_copy(InputIt first, InputIt last, OutputIt d_first)
{
	while (first != last) {
		*d_first++ = *first++;
	}
	return d_first;
}

template<typename Container>
void back_inserter(Container& c)
{
	c.push_back();
}

void testSet() {
	std::set<int> intset;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 10; j++) {
			// Try to insert multiple copies:
			intset.insert(j);
		}
	}
	// Print to output:
	m_copy(intset.begin(), intset.end(), std::ostream_iterator<int>(std::cout, "\n"));
}

void testIterators()
{
	std::vector<int> v{1,2,3,4,5};
	
	for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << endl;

	std::vector<int> fv;
	std::copy(v.begin(), v.end(), std::front_inserter(fv));
	
	std::vector<int> fv;
	std::copy(v.begin(), v.end(), std::back_inserter(fv));
}



void testAlgos()
{
	testIterators();
	testSet();
	int i;
	std::cin >> i;
}
