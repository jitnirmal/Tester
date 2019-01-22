#pragma once
#include <cstddef>
#include <typeinfo>
#include <iostream>
//https://github.com/rigtorp/awesome-modern-cpp
/// /// <summary>
/// //how to print something before main starts...
/// </summary>
int fun1()
{
	std::cout << "this need to be first line" << std::endl;
	return 1;
}
void fun2()
{
	std::cout << "this need to be second line" << std::endl;
}
struct Temp
{
	Temp() {
		fun2();
	}
	static int i;
};
//int Temp::i = fun1();
//Temp t; // global Object that will be called before main....


/// <summary>
/// how to check 2 objects belongs to same class
/// </summary>

struct S {};
struct P {};

template<typename T1,typename T2>
void checkIfObjectsBelongsToSameClass(T1 a, T2 b)
{
	if(typeid(a) == typeid(b))
	{
		std::cout << "same Type" << std::endl;
	}
	else
	{
		std::cout << "Different Type" << std::endl;
	}
}

//--------------------------------------------------------------------------------------------
//				Write data in columns
//--------------------------------------------------------------------------------------------
#include <iomanip>
int WriteDataInColumns(){
	std::cout << std::left << std::setw(12) << "John Smith" 
		<< std::right << std::setw(3) << 23
		<< '\n';
	std::cout << std::left << std::setw(12) << "Sam Brown"
		<< std::right << std::setw(3) << 8
		<< '\n';
}

//--------------------------------------------------------------------------------------------
//				Function template SFINAE (Substitution Failure Is Not An Error )
//--------------------------------------------------------------------------------------------
#include <type_traits>
#include <limits>
#include <cmath>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
equal(T lhs, T rhs)
{
	return lhs == rhs;
}
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
equal(T lhs, T rhs)
{
	return std::abs(lhs - rhs) < 0.0001;
}


void testTricks()
{
	WriteDataInColumns();
	checkIfObjectsBelongsToSameClass(S(),S());
	checkIfObjectsBelongsToSameClass(S(), P());
}


