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
#include <type_traits>

/// <summary>
/// Type traits allow you to make decisions based on types at compile time
///	For example
///		--- you can write a template that requires a type that is derived from a certain type
///		--- type that is convertible to a certain type
///		--- type that is integral, and so on.
/// </summary>
/// 

namespace ttest{
template <class T, T v>
struct integral_constant {
	static constexpr T value = v;
	typedef T value_type;
	typedef integral_constant<T, v> type;
	constexpr operator value_type() const noexcept { return value; }
	constexpr value_type operator()() const noexcept { return value; }
};
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

}

template<> struct is_integral<bool> : public ttest::true_type { };

template<typename T>
void process(const T& t)
{
	if (is_integral<T>::value) {
		cout << t << " is an integral type." << endl;
	}
	else {
		cout << t << " is a non-integral type." << endl;
	}
}
int TestType()
{
	process(123);
	process(2.2);
	process(string("Test"));
}


template<typename T1, typename T2>
void same(const T1& t1, const T2& t2)
{
	bool areTypesTheSame = is_same<T1, T2>::value;
	cout << "'" << t1 << "' and '" << t2 << "' are ";
	cout << (areTypesTheSame ? "the same types." : "different types.") << endl;
}

int TestRelatioship()
{
	same(1, 32);
	same(1, 3.01);
	same(3.01, string("Test"));
}


/// <summary>
/// SFINAE - Substituion failure is not an error
/// </summary>

template<typename T1, typename T2>
typename enable_if<is_same<T1, T2>::value, bool>::type
check_type(const T1& t1, const T2& t2)
{
	cout << "'" << t1 << "' and '" << t2 << "' ";
	cout << "are the same types." << endl;
	return true;
}

template<typename T1, typename T2>
typename enable_if<!is_same<T1, T2>::value, bool>::type
check_type(const T1& t1, const T2& t2)
{
	cout << "'" << t1 << "' and '" << t2 << "' ";
	cout << "are different types." << endl;
	return false;
}
int testSNIFAE()
{
	check_type(1, 32);
	check_type(1, 3.01);
	check_type(3.01, string("Test"));
}

void TestTraits()
{
	TestType();
	TestRelatioship();
	testSNIFAE();
	
}