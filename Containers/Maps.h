#pragma once
#include <unordered_map>
#include <random>
#include <map>
#include <iostream>

using namespace std;

	struct Key
	{
		std::string first;
		std::string second;
		int         third;

		bool operator==(const Key &other) const
		{
			return (first == other.first
				&& second == other.second
				&& third == other.third);
		}
	};

	struct KeyHasher
	{
		std::size_t operator()(const Key& k) const
		{
			size_t res = 17;
			res = res * 31 + hash<string>()(k.first);
			res = res * 31 + hash<string>()(k.second);
			res = res * 31 + hash<int>()(k.third);
			return res;
		}
	};

	//or
	/// <summary>
	/// The class template std::hash is a function object template whose call operator defines a hash function with the following properties :
	/// 1. Takes an argument of the template parameter type and returns a size_t value.
	/// 2. Does not throw any exceptions.
	/// 3. For two arguments that are equal, it returns the same hash value.
	/// 4. For two arguments that are not equal, the probability of returning the same valueis very small
	/// (should be close to	1.0 / std::numeric_limits<size_t>::max()).
	/// 
	/// To compute a good hash value, you should do the following:
	/// 	1. Start with an initial value that should be a prime number(for example, 17).
	///			actually it need to be non-zero, prime number is picked as it can be optmized for multiplication
	///			The use of prime 31 is advantageous for performance optimizations, because 31 * x can be replaced
	///     	by the compiler with(x << 5) - x, which is faster.Similarly, you can use 127, because 
	///			127 * x is equal to(x << 7) - x or 8191, because 8191 * x is equal to(x << 13) -x.
	/// 	2. For each field that is used to determine whether two instances of the class are
	///			equal, adjust the hash value according to the following formula :
	///			hashValue = hashValue * prime + hashFunc(field);
	/// 	3. You can use the same prime number for all fields with the above formula, but it is
	/// 		recommended to have a different value than the initial value(for instance, 31).
	///     4. Use specialization of std::hash to determine the hash value for class data	members.
	/// 
	/// </summary>
	namespace std
	{
		template<>
		struct hash<Key>
		{
			typedef Key argument_type;
			typedef size_t result_type;
			result_type operator()(argument_type const & item) const
			{
				result_type hashValue = 17;
				hashValue = 31 * hashValue +
					std::hash<std::string>{}(item.first);
				hashValue = 31 * hashValue +
					std::hash<std::string>{}(item.second);
				hashValue = 31 * hashValue +
					std::hash<double>{}(item.third);
				return hashValue;
			}
		};
	}


void TestUnorderedMap()
{
	std::unordered_map<Key, std::string, KeyHasher> m6 = {
		{ { "John", "Doe", 12 }, "example" },
	{ { "Mary", "Sue", 21 }, "another" }
	};
}



/// <summary>
/// Map key
/// </summary>

struct MapKey
{
	int _id;
	std::string _name;
	MapKey(std::string name, int id) :
		_id(id), _name(name)
	{
	}

	bool operator<(const MapKey& key) const
	{
		if (key._id < _id)
			return true;
		return false;
	}
};


struct KeyComparator
{
	bool operator()(const MapKey& lhs, const MapKey& rhs) const
	{
		return (lhs._id < rhs._id);
	}
};

void TestMapKeys()
{
	std::map<MapKey, int> map1;
	map1[MapKey("second", 2)] = 2;
	map1[MapKey("first", 1)] = 1;
	map1[MapKey("third", 3)] = 3;

	std::map<MapKey, int, KeyComparator> map2;
	map2[MapKey("third", 3)] = 3;
	map2[MapKey("first", 1)] = 1;
	map2[MapKey("second", 2)] = 2;


	std::map<std::string, int> mapOfWords;
	//Inserting data in std::map
	mapOfWords.insert(std::make_pair("earth", 1));
	mapOfWords.insert(std::make_pair("moon", 2));
	mapOfWords["sun"] = 3;
	mapOfWords["earth"] = 4; // Will siletly replace the value of already added key.

	auto iter = mapOfWords.insert(std::make_pair("earth", 1));
	// iter.second should be 4 only


}

void testMaps()
{

	TestMapKeys();
	int i;
	std::cin >> i;
}
