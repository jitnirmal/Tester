#pragma once

#include <iostream>
using namespace std;

// What is decltype in C++
// It checks the type of expression..

template <typename T1, typename T2>
T2 add1(T1 a, T2 b) {
	return (a + b);
}


template <typename T1, typename T2>
auto add2(T1 a, T2 b) -> decltype(a+b) {
	// not required in c++ 14
	return (a + b);
}



void TestDeclType()
{
	cout << add1(1, 1.8) << std::endl; // 2.8
	cout << add1(1.8, 1) << std::endl; // 2

	cout << add2(1, 1.8) << std::endl; // 2.8
	cout << add2(1.8, 1) << std::endl; // 2.8
}

/// <summary>
/// Singleton with variable arguments
/// </summary>
template<typename T>
class Singleton
{
public:
	Singleton() = delete;
	Singleton(const Singleton&) = delete;
	~Singleton() = delete;

	template<typename ...Args>
	static T& Instance(Args&& ...args)
	{
		static T single(std::forward<Args>(args)...);
		return single;
	}
};
void TestSingleton()
{
	struct X {
		void print()
		{
			puts("X");
		}
	};
	struct Y
	{
		Y(int i, double d, const std::string& s) {}
		void print()
		{
			puts("Y");
		}
	};
	
	auto& x = Singleton<X>::Instance() ;
	x.print();

	auto y = Singleton<Y>::Instance(1,2.3f,"nirmal");
	y.print();
}

void TestFunctions()
{
	TestSingleton();
	//TestDeclType();

}
