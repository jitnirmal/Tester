#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <cassert>


using namespace std;

class Cheap {
public:
	Cheap(int i_ = -1) : i(i_) {}
	using key_type= int;
	key_type get_key() const { return i; }
	bool operator< (const Cheap& rhs) const { return i < rhs.i; }
	bool operator== (const Cheap& rhs) const { return i == rhs.i; }
	friend ostream& operator<< (ostream& os, const Cheap& x);
	void print() const { cout << *this << endl; }
private:
	int i;
};


class Expensive {
public:
	Expensive(int i = -1)
	{
		// name strings the same length, differing only in the last few characters
		ostringstream oss;
		oss << "abcdefghijklmnopqrstuvwxyz" << 10000000 + i;
		s = oss.str();
	}
	using key_type= string;
	const key_type& get_key() const { return s; }
	bool operator< (const Expensive& rhs) const { return s < rhs.s; }
	bool operator== (const Expensive& rhs) const { return s == rhs.s; }
	friend ostream& operator<< (ostream& os, const Expensive& x);
private:
	string s;
};

// A hash function object class template to be specialized for the different types
template <typename T>
class HashFn {
public:
	size_t operator()(const T&) const
	{
		assert(!"MyHash unspecialized operator() has been called!"); return 0;
	}
};

template <>
class HashFn<Cheap> {
public:
	size_t operator()(const Cheap& c) const
	{
		return static_cast<size_t>(c.get_key()); 
	}
};

template <>
class HashFn<Expensive> {
public:
	size_t operator()(const Expensive& e) const
	{
		const string& s = e.get_key();
		size_t result = 0;
		for (string::const_iterator i = s.begin(); i != s.end(); ++i)
			result = (result * 131) + *i;
		return result;
	}
};

template <typename T>
class Set_tester {
public:
	Set_tester(const vector<T>& initial_load) :
		container(initial_load.begin(), initial_load.end())
	{
		
	}
	bool operator() (const T& item)
	{
		return (container.find(item) != container.end());
	}
private:
	std::set<T> container;
};

template <typename T>
class USet_tester {
public:
	USet_tester(const vector<T>& initial_load) :
		container(initial_load.begin(), initial_load.end())
	{
		
	}
	// search for the supplied item
	bool operator() (const T& item)
	{
		return (container.find(item) != container.end());
	}
private:
	std::unordered_set<T, HashFn<T> > container;
};




