#pragma once

#include <iostream>

#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

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