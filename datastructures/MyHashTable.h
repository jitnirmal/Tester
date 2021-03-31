#pragma once
#include<vector>
#include<list>
#include<algorithm>
#include<cassert>
#include<unordered_map>
#include<iostream>
/// <summary>
/// The first strategy, commonly known as "separate chaining", is to keep a list of all elements that hash to the same value
///  We define the load factor, λ, of a hash table to be the ratio of the number of elements in the hash table to the table size.
/// The effort required to perform a search is the constant time required to evaluate the hash function plus the time to traverse the list.
///  rehashing is a very expensive operation; the running time is O(N), since there are N elements to rehash and the table size is roughly 2N
/// 
/// 
/// The items in the ordered_set(or the keys in the unordered_map) must provide an overloaded operator== and a hash function,
/// </summary>

template <typename Key>
class hash
{
public:
	size_t operator() (const Key& k) const
	{
		size_t hashVal = 17;
		hashVal = 37 * hashVal + k;
		return hashVal;
	}
};

template<>
class hash<std::string>
{
public:
	size_t operator()(const std::string& key)
	{
		size_t hashVal = 0;
		for (char ch : key)
			hashVal = 37 * hashVal + ch;
		return hashVal;
	}
};

struct A
{
	A(int i) :IntI(i) {}
	int IntI = 0;

	bool operator==(const A& rhs) const
	{
		return rhs.IntI == IntI;
	}
};

template<>
class hash<A>
{
public:
	size_t operator()(const A& key)
	{
		size_t hashVal = 17;
		hashVal = 37 * hashVal + key.IntI;
		return hashVal;
	}
};


template <typename Key, typename Value>
class HashTable
{
public:
	typedef Key    key_type;
	typedef Value  value_type;
	typedef std::pair<const Key, Value> key_value_type;

	explicit HashTable(int size = 101) :_size(0) {
		for (size_t i = 0; i < size; ++i)
		{
			_tableOfLists.push_back(std::list<key_value_type>());
		}
	}

	bool contains(const key_type& key) const
	{
		auto& searchList = _tableOfLists[getHashCode(key)];
		return (std::find_if(std::begin(searchList), std::end(searchList),
			[&key](const key_value_type & kv) { return kv.first == key; }) != std::end(searchList));
	}

	void makeEmpty() {
		for (auto& thisList : _tableOfLists)
			thisList.clear();
	}

	value_type& insert(const key_value_type & kv)
	{
		auto& currentList = _tableOfLists[getHashCode(kv.first)];

		auto result = std::find_if(std::begin(currentList), std::end(currentList),
			[&kv](const key_value_type & lkv) { return lkv.first == kv.first; });

		if (result != end(currentList))
			return (*result).second;

		currentList.push_back(kv);

		if (++_size > _tableOfLists.size())
			rehash();

		return currentList.back().second;
	}

	value_type& insert(const key_type & key, const value_type & value)
	{
		return insert(key_value_type(key, value));
	}

	value_type& operator[](const key_type & key)
	{
		return insert(key_value_type(key, value_type()));
	}

	bool remove(const key_type & key)
	{
		auto& currentList = _tableOfLists[getHashCode(key)];
		auto itr = (std::find_if(std::begin(currentList), std::end(currentList),
			[&key](const key_value_type & kv) { return kv.first == key; }));

		if (itr == end(currentList))
			return false;

		currentList.erase(itr);
		--_size;
		return true;
	}
private:
	void rehash()
	{
		std::vector<std::list<key_value_type>> oldLists = _tableOfLists;

		// Create new double-sized, empty table
		_tableOfLists.resize(2 * _tableOfLists.size());
		for (auto& thisList : _tableOfLists)
			thisList.clear();

		// Copy table over
		_size = 0;
		for (auto& thisList : oldLists)
			for (auto& x : thisList)
				insert(std::move(x));
	}

	size_t getHashCode(const key_type & x) const
	{
		static hash<key_type> hf;
		return hf(x) % _tableOfLists.size();
	}

private:
	std::vector<std::list<key_value_type>> _tableOfLists; // The array of Lists
	int _size;
};

void TestHashTableInt()
{
	HashTable<int, int> HT;
	HT.insert(1, 10);
	HT.insert(2, 10);
	if (HT.contains(2))
	{
		HT.insert(2, 10);
	}
	auto res = HT.insert(3, 11);
	auto res1 = HT[4] = 12;
	auto result = HT[4];
}


void TestHashTableStruct()
{
	HashTable<A, int> HT;
	HT.insert(A(1), 10);
	HT.insert(A(2), 10);
	if (HT.contains(A(2)))
	{
		HT.insert(A(2), 10);
	}
	auto res = HT.insert(A(3), 11);
	auto res1 = HT[A(4)] = 12;
	auto result = HT[A(4)];

	HT.remove(A(4));
	auto result2 = HT[A(4)];
}
