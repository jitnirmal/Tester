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

void testFactorial()
{
	constexpr auto result1 = cefactorial(10);
	constexpr auto result2 = tfactorial<10>::value;
	constexpr auto result3 = t2factorial<10>::value;
}

/********************************************************************************/
template<int X, int Y>
struct Adder
{
	enum { result = X + Y };
};

void testAdder()
{
	constexpr auto adder = Adder<10, 20>::result;
}
/********************************************************************************/

/********************************************************************************/
template <unsigned long N>
struct binary
{
	static unsigned const value
		= binary<N / 10>::value << 1 // prepend higher bits
		| N % 10; // to lowest bit
};

template <> // specialization
struct binary<0> // terminates recursion
{
	static unsigned const value = 0;
};

unsigned binaryRecursive(unsigned long N)
{
	return N == 0 ? 0 : N % 10 + 2 * binaryRecursive(N / 10);
}

unsigned binaryLoop(unsigned long N)
{
	unsigned result = 0;
	for (unsigned bit = 0x1; N; N /= 10, bit <<= 1)
	{
		if (N % 10)
			result += bit;
	}
	return result;
}

void testBinary()
{
	unsigned const one = binary<1>::value;
	unsigned const three = binary<11>::value;
	unsigned const five = binary<101>::value;
	unsigned const seven = binary<111>::value;
	unsigned const nine = binary<1001>::value;
	
	auto result = binaryLoop(1001);


}



void templateTest()
{
	//testFactorial();
	//testAdder();
	testBinary();
}