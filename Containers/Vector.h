#pragma once
#include <unordered_map>
#include <random>
#include <iostream>
#include <queue>
#include <map>
#include <functional>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
/// <summary>
/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-1          STD::VECTOR
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. provide good locality, also known as cache-friendliness
/// 2. when a vector reallocates its underlying array, the elements change addresses (iterator invalidation)
/// 3. When the vector resizes, it reallocates its underlying array and moves its elements into the new array--
///     unless the element type is not "nothrow moveconstructible," in which case it copies its elements
///     A good rule of thumb is: Whenever you declare your own move constructor or swap function, make sure you declare it noexcept.
/// 4. vec.emplace_back(args...) is a perfect-forwarding variadic function template that acts just like.push_back(t), 
/// except that, instead of placing a copy of t at the end of the vector, it places a T object constructed as if by T(args...).
/// Both push_back and emplace_back have what is called "amortized constant time" performance.
/// 
/// The std::vector template has one special case: std::vector<bool>.
/// Since the bool datatype has only two possible values, the values of eight bools can be packed into a single byte.
/// it uses eight times less heap - allocated memory than you might naturally expect
/// 5. Insert time: from back aggregate O(1), from elsewhere O(n)
/// 6. Index time: by position, in O(1)
/// 7. Sort in O(n log2 n)
/// 8. Search in O(log2 n) if sorted, else O(n)
/// </summary>

/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-2          STD::DEQUE
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. its elements are only "chunkwise" contiguous, single deque is made up of an arbitrary number of "chunks," each containing a 
///   fixed number of elements.
/// 2. To insert more elements on either end of the container is cheap O(1); to insert elements in the middle is still expensive O (n)
///     In addition to vector's push_back and pop_back methods, deque exposes an efficient push_front and pop_front.
/// 3. The disadvantage of std::deque<T> is that its iterators are significantly more expensive to increment and dereference, 
///      since they have to navigate the array of pointers. unless you happen to need quick insertion and deletion at both ends of 
///      the container, vector is more efficient
/// 4. Sort in O(n log2 n)
/// 5. Search in O(log2 n) if sorted, else O(n) 
/// 6. std::deque does not offer any equivalent to std::vector’s reserve() member function to preallocate its internal data structures
/// 7. Inserting at the back and at the front was about twice as expensive as push_back() or push_front(), respectively.
/// 
/// VECTOR VS DEQUE performance
///		1. A vector performs 
///			a) an assignment 13 times faster for the same number of entries.
///			b) 22 times faster at deletion
///			c) 9 times faster at iterator - based insertion
///			d) twice as fast at push_back(), and 3 times as fast when inserting at the end.
/// 
/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-3          STD::LIST
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. doubly linked list, bidirectional iterator, but no random access
/// 2. std::list is much less performant than a contiguous data structure such as std::vector or std::deque, because following 
///      pointers to "randomly" allocated addresses is much harder (less cache friendly)
/// 3. no iterator invalidation
/// 4. lst.push_back(v) and lst.push_front(v) always operate in constant time, and don't ever need to "resize" or "move" any data.
/// 5. lst.splice(it, otherlst) "splices" the entirety of otherlst into lst, The entire splicing operation can be done 
///     with just a couple of pointer swaps. lst.merge(otherlst) similarly empties out otherlst into lst using only pointer swaps,
/// 6. lst.reverse() is very efficient, only with pointer swaps for head and tail are required.
/// 7. lst.sort() sorts the list in-place, Sort in O(n log2 n)
/// 8. lst.remove(v) removes and erases all elements equal to v.
/// 9. Performance wrt Vector
///		a. Pushing incrementally onto the tail of a list is less than twice as expensive as for a unreserved vector.
///		b. Traversing and sorting a list are only 30% more expensive than the same operations on a vector.
///		c. Iterating through the list of 100,000 was 48% more expensive than traversing a vector.
///		d. std::sort takes O(n2). it is due to the fact that cost to find the distance, 
///			or number of items between two bidirectional iterators,is O(n).
///		e. std::list has a built-in sort that is more efficient, at O(n log2 n). Sorting the list using 
///			std::list’s built in sort() took 25 % longer than sorting the equivalent vector.
///		f. Because std::list provides only bidirectional iterators, the binary-search algorithms are all O(n) for lists.
///			Searching with std::find() is also O(n), This makes std::list a poor candidate to replace associative containers.

/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-4          STD::FORWARD_LIST
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. no way to get its size, no way to iterate backward
/// 2. std::forward_list retains almost all of the "special skills" of std::list. The only operations that it can't do are 
///  splice (because that involves inserting "before" the given iterator) and push_back(because that involves finding the end of the list in constant time).
///  Performance
///		a. iteration take 45% more time than vector
///		b. std::list, std::forward_list has a built-in sort that runs in O(n log2 n).
///		c. provides only forward iterators, the binary-search algorithms are O(n) for forward lists.Searching with the far simpler std::find() is also O(n)

/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-5          STD::STACK and STD::QUEUE
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. std::stack<T, Ctr> is container adapter (LIFO) stack<T,vector<T >> uses vector, and stack<T,List<T>> uses List, default is td::deque<T>
/// 2. main operations -- Push, Pop, Top 
/// 3. std::queue<T, Ctr> again uses low-overhead double-ended queue
/// 4. push_back and pop_front

/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-5          STD::priority_queue std::priority_queue<T, Ctr, Cmp>
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element,
///    at the expense of logarithmic insertion and extraction.
/// 2. A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the smallest element to appear as the top().
///      default value of Ctr in this case is std::vector<T>.
/// 2. The default value of Cmp is the standard library type std::less<T>
/// 3. main operations -- Push, Pop, Top 
void TestPriorityQueue()
{
	std::priority_queue<int> pq1;
	std::priority_queue<int, std::vector<int>, std::greater<>> pq2;
	for (int v : {3, 1, 4, 1, 5, 9}) {
		pq1.push(v);
		pq2.push(v);
	}
	assert(pq1.top() == 9); // max-heap by default
	assert(pq2.top() == 1); // min-heap by choice
}


/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-6          STD::SET
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. std::set is an associative container that contains a sorted set of unique objects of type Key. 
/// 2. Sorting is done using the key comparison function Compare. 
/// 3. Search, removal, and insertion operations have logarithmic complexity. 
/// 4. Sets are usually implemented as red-black trees
/// 5. s.insert(v) return pair
///			-- ret.first is the usual iterator to the copy of v now in the data structure
///         -- and ret.second is true if the pointed-to v was just inserted and false if the pointed - to v was already in the set 
/// 6. s.count(v) will only ever return 0 or 1
/// 7. std::map and std::set are so cache-unfriendly that you should avoid them by default and prefer to use std::unordered_map and std::unordered_set instead
/// 8. Iterators and references never invalidated except for removed items
/// 
/// NOTE : One difference between std::map and std::set is that the items returned by set lookup are const.
///					If you really want to use the set abstraction, fields in the value data type that don’t participate in the ordering 
///					relationship can be declared mutable, specifying that they don’t participate in the ordering relationship.
///					Otherwise do not change members that participate in the ordering relation, or the set data structure will become invalid.
/// 
/// performance:
///		a. Iterating through the 100,000-item map took 10 times longer than iterating through a vector.
///		b. if the numher of elements are constant, sorted vector can give much better performance (100000 elements)
///					Container		Insert+sort		Lookup
/// 				Vector			20 ms			29 ms
///					Map				34 ms			43 ms
///			If the table will change frequently, with insertions or deletions, re - sorting the vector - 
///				based table will consume any advantage it may have had in search time.
///			
void TestMap()
{
	std::map<std::string, std::string> m;
	m["hello"] = "world";
	m["quick"] = "brown";
	m["hello"] = "dolly";
	assert(m.size() == 2);
	using Pair = decltype(m)::value_type;

	if (m.find("hello") == m.end()) {
		m.insert(Pair{ "hello", "dolly" });
		// ...or equivalently...
		m.emplace("hello", "dolly");
	}
}

/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-6          STD::UNORDERED_SET/MAP	
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. chained hash table, fixed-size array of "buckets," each bucket containing a singly linked list of data elements.
/// /// 2. As new data elements are added to the container, each element is placed in the linked list associated with the "hash" of the element's value
/// 3. designed to be a drop-in replacement for std::set,
/// 4. the elements of a std::unordered_set are not stored in sorted order
/// 5. s.load_factor() returns s.size() / s.bucket_count() as a float value
/// 6. s.rehash(n) increases (or decreases) the size of the bucket array to exactly n.
/// 7. Each unordered_set object s has a value s.max_load_factor() indicating exactly how large s.load_factor() is allowed to get
/// 8. If an insertion would push s.load_factor() over the top, then s will reallocate its array of buckets and rehash its elements 
///     in order to keep s.load_factor() smaller than s.max_load_factor().
/// 9. s.reserve(k). Like vec.reserve(k) for vectors, help to save reallocations.
///  10. Performance
///			a. Insert time: O(1) average, O(n) worst case
///			b. Iterators invalidated on rehash, references invalidated only for removed items
///			c. Using a std hash function, 15% of entries collided, and that the automatic allocation 
///				produced a table with a load factor of 0.38, meaning that 62 % of the backbone array was unused.
///			d. The insertion test took 15.5 milliseconds. Insertion performance can be improved somewhat by preallocating sufficient buckets to prevent 
///					rehashing, through a call to reserve().
///			e. An unordered map cannot be sorted, and iterating through an unordered map produces 
///				items in an opaque order (3 times slower than vector)
/// 		f. performance comparison(100000 elements)
///					Container		Insert+sort		Lookup
///					Map				34 ms			43 ms
/// 				Vector			20 ms			29 ms
/// 	
/// 			Unordered map   16 ms			11 ms

/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-7          OTHER DATA STRUCTURES
/// -------------------------------------------------------------------------------------------------------------------------------------
/// boost::circular_buffer : Similar in many respects to std::deque, but more efficient.
/// Boost.Container		   : Variations on standard library containers such as a 
///							stable vector (a vector in which reallocation doesn’t invalidate iterators)
///							 a map / multimap / set / multiset implemented as a container adapter for std::vector
///							 a static vector with variable length up to a fixed maximum, 
///							and a vector with optimized behavior when the vector has only a few elements.
/// Boost Graph Library (BGL) : Algorithms and data structures for graph traversal.
/// boost.heap				  : A priority queue with better performance 
/// boost.lockfree			  : Lock - free and wait - free queue and stack.
/// Boost.MultiIndex		  : Containers that have multiple indices with different behaviors.
/// Boost.Intrusive			  : Provides intrusive containers(containers that rely on node types that explicitly
///								contain links).The point of intrusive containers is to improve performance in
///								very hot code.This library contains singly and doubly linked lists, associative
///								containers, unordered associative containers, and a variety of explicit balanced
///								tree implementations. make_shared, along with move semantics and the 
///								emplace() member functions added to most containers, reduces the need for intrusive containers.


void TestHash()
{
	class Widget {
	public:
		virtual bool IsEqualTo(Widget const *b) const;
		virtual int GetHashValue() const;
	};
	struct getHashCode {
		size_t operator()(const Widget *w) const {
			return w->GetHashValue();
		}
	};
	struct myequal {
		bool operator()(const Widget *a, const Widget *b) const {
			return a->IsEqualTo(b);
		}
	};
	std::unordered_set<Widget *, getHashCode, myequal> s;
}

template<typename T> 
void hash_stats(T const& table) {
	unsigned zeros = 0;
	unsigned ones = 0;
	unsigned many = 0;
	unsigned many_sigma = 0;
	for (unsigned i = 0; i < table.bucket_count(); ++i) {
		unsigned how_many_this_bucket = 0;
		for (auto it = table.begin(i); it != table.end(i); ++it) {
			how_many_this_bucket += 1;
		}
		switch (how_many_this_bucket) {
		case 0:
			zeros += 1;
			break;
		case 1:
			ones += 1;
			break;
		default:
			many += 1;
			many_sigma += how_many_this_bucket;
			break;
		}
	}
	std::cout << "unordered_map with " << table.size()
		<< " entries" << std::endl
		<< " " << table.bucket_count() << " buckets"
		<< " load factor " << table.load_factor()
		<< ", max load factor "
		<< table.max_load_factor() << std::endl;
	if (ones > 0 && many > 0)
		std::cout << " " << zeros << " empty buckets, "
		<< ones << " buckets with one entry, "
		<< many << " buckets with multiple entries, "
		<< std::endl;
	if (many > 0)
		std::cout << " average length of multi-entry chain "
		<< ((float)many_sigma) / many << std::endl;
}

void TestVector()
{

}