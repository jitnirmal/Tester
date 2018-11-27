#include <iostream>


/// <summary>
/// for (auto x : range) { code_block; }
/// 
/// The compiler will evaluate it to the following:
/// { 
///     auto __begin = std::begin(range);   
///     auto __end   = std::end(range);    
///		for ( ; __begin != __end; ++__begin) 
///		{
///		         auto x = *__begin;
///		         code_block
///     }
///  }
/// 
/// While looking at this code, it becomes obvious that the only requirements for the iterators are the following three operators:
///		operator!=: unequal comparison
///		operator++ : prefix increment
///		operator* : dereference
/// /// </summary>

class num_iterator {
	int i;
public:
	explicit num_iterator(int position = 0) : i{ position } {}
	int operator*() const { return i; }
	num_iterator& operator++() {
		++i;
		return *this;
	}
	bool operator!=(const num_iterator &other) const {
		return i != other.i;
	}
	bool operator==(const num_iterator &other) const {
		return !(*this != other);
	}
};

/// <summary>
/// intermediate object for writing for (int i : intermediate(a, b)) {...}, 
/// which contains the begin and end iterator, 
/// which is preprogrammed to iterate from a to b.
/// </summary>
class num_range {
	int a;
	int b;

public:
	num_range(int from, int to)
		: a{ from }, b{ to }
	{}
	num_iterator begin() const { return num_iterator{ a }; }
	num_iterator end()   const { return num_iterator{ b }; }
};

void testRangeIterator()
{
	for (int i : num_range{ 100, 110 }) {
		std::cout << i << ", ";
	}
	std::cout << '\n';
}


