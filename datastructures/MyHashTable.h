#pragma once
#include<vector>
#include<list>
#include<algorithm>
#include<cassert>

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
	size_t operator() (const Key & k) const
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
		size_t operator()(const std::string & key)
		{
			size_t hashVal = 0;
			for (char ch : key)
				hashVal = 37 * hashVal + ch;
			return hashVal;
		}
};

template <typename T>
class HashTable
{
public:
	explicit HashTable(int size = 101):_size(0) {
		for (unsigned int i = 0; i < size; ++i)
		{
			_tableOfLists.push_back(std::list<T>());
		}
	}

	bool contains(const T& x) const
	{
		auto& searchList = _tableOfLists[getHashCode(x)];
		return (std::find(std::begin(searchList), std::end(searchList), x) != std::end(searchList));
	}

	void makeEmpty() {
		for (auto & thisList : _tableOfLists)
			thisList.clear();
	}

	bool insert(const T& x) {
		auto & currentList = _tableOfLists[getHashCode(x)];
		if (find(begin(currentList), end(currentList), x) != end(currentList))
			return false;
		currentList.push_back(x);
		
		if (++_size > _tableOfLists.size())
			rehash();
		return true;
	}

	//bool insert(T&& x);

	bool remove(const T& x) {
		auto & currentList = _tableOfLists[getHashCode(x)];
		auto itr = std::find(std::begin(currentList), std::end(currentList), x);
		if (itr == end(currentList))
			return false;
		
		currentList.erase(itr);
		--_size;
		return true;
	}

private:
	void rehash() {
		std::vector<std::list<T>> oldLists = _tableOfLists;
	 
		// Create new double-sized, empty table
		_tableOfLists.resize(2 * _tableOfLists.size());
		for (auto & thisList : _tableOfLists)
			thisList.clear();
		
		// Copy table over
		_size = 0;
		for (auto & thisList : oldLists)
			for (auto & x : thisList)
			 insert(std::move(x));
	}

	size_t getHashCode(const T & x) const {
		static hash<T> hf;
		return hf(x) % _tableOfLists.size();
	}

private:
	std::vector<std::list<T>> _tableOfLists; // The array of Lists
	int _size;
};

void TestHashTable()
{
	HashTable<int> HT;
	HT.insert(10);
	assert(HT.contains(10)==true);

}