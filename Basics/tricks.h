#pragma once
#include <cstddef>
#include <typeinfo>

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

void testTricks()
{
	checkIfObjectsBelongsToSameClass(S(),S());
	checkIfObjectsBelongsToSameClass(S(), P());
}