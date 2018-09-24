#pragma once

#include <iostream>
/********************************************************************************/
template <unsigned n>
struct tfactorial
{
	enum { value = n * tfactorial<n - 1>::value };
};

template <>
struct tfactorial<0>
{
	enum { value = 1 };
};

/********************************************************************************/
template <unsigned n>
struct t2factorial
{
	static const unsigned int value = n * t2factorial<n - 1>::value;
};

template <>
struct t2factorial<0>
{
	static const unsigned int value = 1;
};
/********************************************************************************/

constexpr unsigned int cefactorial(const unsigned int n)
{
	return (n > 1 ? n* cefactorial(n-1) : 1);
}

/********************************************************************************/
template<int X, int Y>
struct Adder
{
	enum { result = X + Y };
};
/********************************************************************************/

/********************************************************************************/

void templateTest()
{
	constexpr auto result1 = cefactorial(10);
	constexpr auto result2 = tfactorial<10>::value;
	constexpr auto result3 = t2factorial<10>::value;
	constexpr auto adder = Adder<10,20>::result;
}