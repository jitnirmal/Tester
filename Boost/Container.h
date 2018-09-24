#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <unordered_set>

struct Name {
	std::string first_name;
	std::string last_name;
};
bool operator==(const Name& lhs, const Name& rhs) {
	return lhs.first_name == rhs.first_name && lhs.last_name == rhs.last_name;
}

// custom hash can be a standalone function object:
struct MyHash
{
	std::size_t operator()(Name const& s) const noexcept
	{
		std::size_t h1 = std::hash<std::string>{}(s.first_name);
		std::size_t h2 = std::hash<std::string>{}(s.last_name);
		return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
	}
};



/*

std::size_t hash_value(const animal &a)
{
	std::size_t seed = 0;
	boost::hash_combine(seed, a.name);
	boost::hash_combine(seed, a.legs);
	return seed;
}
*/

void testBoostMap()
{
	std::string str = "Test the hash string...";

	std::size_t str_hash = std::hash<std::string>{}(str);
	std::cout << "hash(" << std::quoted(str) << ") = " << str_hash << '\n';

	std::unordered_set<Name, MyHash> names = { { "Samarveer", "Singh" },{ "Manseerat", "Kaur" } };
	for (auto& s : names)
		std::cout << std::quoted(s.first_name) << ' ' << std::quoted(s.last_name) << '\n';

	std::cout << "size = " << names.size() << std::endl;
	std::cout << "bucket_count = " << names.bucket_count() << std::endl;
	std::cout << "load_factor = " << names.load_factor() << std::endl;
	std::cout << "max_load_factor = " << names.max_load_factor() << std::endl;


	names.rehash(1000);
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "size = " << names.size() << std::endl;
	std::cout << "bucket_count = " << names.bucket_count() << std::endl;
	std::cout << "load_factor = " << names.load_factor() << std::endl;
	std::cout << "max_load_factor = " << names.max_load_factor() << std::endl;

}