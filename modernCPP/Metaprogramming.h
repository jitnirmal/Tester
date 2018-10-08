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
#include <type_traits>

#include <limits>
/// <summary>
/// template specializtion
/// </summary>

/// <summary>
/// Loop Unrolling :unroll loops at compile time instead of run time.
///  Note that most of time compiler is smart enough to unroll loops that can be unrolled for you
/// </summary>
template<int i>
class Loop
{
public:
	template <typename F, typename... Args>
	static inline void Do(F func,Args... args) {
		Loop<i - 1>::Do(func,args...);
		func(i, std::forward<Args>(args)...);
	}
};

template<>
class Loop<0>
{
public:
	template <typename F, typename... Args>
	static inline void Do(F func, Args... args) {}
};
void DoWork(int i) { std::cout << "DoWork(" << i << ")" << std::endl; }

void TestLoopUnRolling()
{
	Loop<3>::Do(DoWork);
}

/// <summary>
/// Printing Tuples..
/// </summary>
template<int n, typename TupleType>
class tuple_print_helper
{
public:
	tuple_print_helper(const TupleType& t) {
		tuple_print_helper<n - 1, TupleType> tp(t);
		std::cout << std::get<n - 1>(t) << std::endl;
	}
};

template<typename TupleType>
class tuple_print_helper<0, TupleType>
{
public:
	tuple_print_helper(const TupleType&) { }
};

template<typename T>
void tuple_print(const T& t)
{
	tuple_print_helper<tuple_size<T>::value, T> tph(t);
}

void TestTuple()
{
	auto t1 = make_tuple(167, "Testing", false, 2.3);
	tuple_print(t1);
}



/// <summary>
/// 
/// 
/// /// </summary>
template<typename T, T Value>
struct m_integral_constant
{
	using type = T;
	static constexpr T value = Value;
};


template<class T>
struct as_constref
{
	using type = T const&;
};

void testMUtils() {
	using cref = as_constref<float>::type;
	using ic  = m_integral_constant<int, 20>;

	std::cout << ic::value << std::endl;
}




void TestMetaprogramming()
{
	//TestLoopUnRolling();
	//TestTuple();

}