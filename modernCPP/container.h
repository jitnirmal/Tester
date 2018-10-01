#pragma once

#include <iostream>

#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
/// <summary>
/// template specializtion
/// </summary>

template<typename T> 
std::string stringify(const T& x)
{
	std::ostringstream out;
	out << x;
	return out.str();
}
template<> 
std::string stringify<bool>(const bool& x)
{
	std::ostringstream out;
	out << std::boolalpha << x;
	return out.str();
}

template<> 
std::string stringify<double>(const double& x)
{
	const int sigdigits = std::numeric_limits<double>::digits10;
	std::ostringstream out;
	out << std::setprecision(sigdigits) << x;
	return out.str();
}
template<> 
std::string stringify<float>(const float& x)
{
	const int sigdigits = std::numeric_limits<float>::digits10;
	std::ostringstream out;
	out << std::setprecision(sigdigits) << x;
	return out.str();
}
template<> 
std::string stringify<long double>(const long double& x)
{
	const int sigdigits = std::numeric_limits<long double>::digits10;
	std::ostringstream out;
	out << std::setprecision(sigdigits) << x;
	return out.str();
}


template <typename Container> 
void print_container(Container& c)
{
	for (auto i : c)
	{
		std::cout << i << ", ";
	}
	std::cout << "\n";
}


/// <summary>
///the number and type of arguments in the template template parameter declaration must match exactly the number and type of arguments 
/// in the definition of the corresponding class template you want to pass as a template argument, regardless of the fact that some of 
/// those parameters may have default values. For instance, the class template std::vector accepts two template parameters
/// (the element type and the allocator type), although the second one has the default value std::allocator<T>.Because of this, you could not write :
/// </summary>
template<typename T, template <typename, typename = std::allocator<T>> class Container>
class TestQ
{
public:
	void push(const T& data)
	{
		_Q.push_back(data);
	}
	
	T pop()
	{
		T data = _Q.front();
		return data;
	}

private:
	Container<T> _Q;
};

/// <summary>
/// container-template that allows my users to supply the type of the underlying container that actually stores the values?
/// 1. containers have  a value_type typedef. use it
/// </summary>
template<typename Underlying>
class ContainerA {
public:
	
	// typename value_type is the type of the values within a Foo-container
	typedef typename Underlying::value_type  value_type;
	//using value_type=Underlying::value_type; 
	void insert(const typename value_type& x)
	{
		// ...code to insert x into data_...
	}
	// ...
private:
	Underlying data_;
};

/// <summary>
/// If you want to allow your users to provide you with an underlying container that does not necessarily have a value_type typedef
/// </summary>
template<typename T, typename Underlying>
class ContainerB {
public:
	// typename value_type is the type of the values within a Foo-container
	typedef T  value_type;
	void insert(const typename value_type& x)
	{
		// ...code to insert x into data_...
	}
	// ...
private:
	Underlying data_;
};


/// <summary>
/// 
/// </summary>
/// 

template<typename T>
struct wrap_vector {
	typedef std::vector<T> type;
};
template<typename T, template<typename> class C>
class ContainerC {
	typename C<T>::type data;  // trick to use a proxy
};


void testContainerA()
{
	ContainerA<std::vector<int> > aX;
	ContainerA<std::list<double> > aY;

	ContainerB<int, std::vector<int> > bX;
	ContainerB<double, std::list<double> > bY;
}


template<template <typename... Args> class Container, 
	typename... Types>
class TestQ2
{
private:
public:
	void insert(Types... types)
	{
		_Q[types]
	}
public:
	Container<Types...> _Q;

};




void TestContainer()
{
	testContainerA();

	std::vector<int> vd = { 1,2,3,4,5};
	print_container(vd);

	std::deque<double> dd = {3.4,5.6,7.9};
	print_container(dd);

	TestQ<int, std::vector> tq;
	tq.push(10);
	auto data = tq.pop();


	TestQ2<std::vector, int> t;
	TestQ2<std::set, std::string> p;

	TestQ2<std::map, std::string, std::string> m;
}