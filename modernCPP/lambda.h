#pragma once
#include <iostream>
#include <iostream>
#include <functional>
#include <array>
#include <cstdlib> // for malloc() and free()
using namespace std;

//https://shaharmike.com/cpp/lambdas-and-functions/
/// <summary>
/// Lambda - fancy name for anonymous functions
///			-- easy way to write functions (such as callbacks) in the logical place they should be in the code
///			-- empty lambda [](){}();
///			-- std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
///			-- [&] means ‘capture by-reference', [=] means ‘capture by-value' 
///			-- a very convenient shorthand notation to introduce functors
///	Similarities between a Lambda and a class
///			--- The class only consists of one member function.
///			--- The capture block is a combination of the class's member variables and its constructor.
///			--- Each lambda function has its own unique type.Even if two lambda functions are plain clones of each other, they still have their own unique type.
/// Advantages over C++ 98 functors
///			-- code remains where it need to be, rather than defining global funciton or functors
///			-- it does not pollute any namespace 
/// Lambda parts
///			a) Capture list – these are variables that are copied inside the lambda to be used in the code;
///				int a, b, c; auto func = [&, c]() {}; 
///					--Capture a, b by reference.Capture c by value.
///			b) Argument list – these are the arguments that are passed to the lambda at execution time;
///			c) Code 
///	lambdas are like classes:
///			a) Captures are the data members // int i = 0, j = 1; auto func = [i, &j](bool b, float f) {
///			b) The data members for f above are i and j;
///			c) The lambda can access these members inside it’s code scope.
///			d) When a lambda is created, a constructor copies the captured variables to the data members;
///			e) It has an operator()(...) (for f the ... is bool, float);
///			g) It has a scope-lifetime and a destructor which frees members.
/// Lambda’s type
///			a)  lambda is not a std::function, though it can be assigned to std::funtion
///			b)  lamda is implementation defined, and the only way to capture a lambda with no conversion is by using auto
///			c)   if your capture list is empty you may convert your lambda to a C-style function pointer, otherwise not
///				
/// mutable lambdas
///			a) lambda’s operator() is const by-default, meaning it can’t modify the variables it captured by-value 
///			b) if you want to change the value paramters, use mutable with lambda, that also only changes the valued inside lambad not outside
///			 -- auto v = 7; auto lambda = [v]() mutable {++v;};
///			-- If we want to capture the v by reference instead, we do not have to specify the mutable keyword as the lambda itself doesn't mutate.
/// Performance
///			-- Because they are objects rather than pointers they can be inlined very easily by the compiler, much like functors
///			--  calling a lambda many times (such as with std::sort or std::copy_if) is much better than using a global function
///			-- This is one example of where C++ is actually faster than C.
///			--  using [=] does not mean that all variables in the scope are copied into the lambda, only the variables actually utilized are copied.
/// /// </summary>
/// 

/// <summary>
/// std::function :  is a templated object that is used to store and call any callable type such as 
///			-- functions
///			-- objects
///			-- lambdas 
///			-- result of std::bind
/// The threshold beyond which std::function reverts to dynamic allocation 17 bytes on clang, 33 bytes on windows. 
///		Note that the allocation is for the size of 17 bytes as the lambda object needs to be contiguous in memory.
/// </summary>




void TestLamda1()
{
	int i = 2;
	int j = 12;
	int k = 15;
	auto sum = [i,j,&k]() { return i + j + k; };

	std::cout << typeid(sum).name() << std::endl;
	//class <lambda_c1f77e36b67d96da861349d9db0191b4>

	std::cout << sizeof(sum) << std::endl;
	// size 8 if it uses 2 variables, otherwise size is 12 if it uses 3 variables.
	
	
	int(*foo)(int, int);
	foo = [](int x, int y) {
		return x+y;
	};


	[&i]() { i = 1; }; // ok, 'i' is captured by-reference.
	//[i]() { i = 1; }; // ERROR: assignment of read-only variable 'i'.
	[i]() mutable { i = 10; }; // ok.
	std::cout << i << std::endl;

}

void TestLambda2() {
	{
		auto th = 3;
		auto is_above = [&th](int v) {
			return v > th;
		};
		auto test = is_above(5);
	}

	// equivalent code is
	{
		auto th = 3;
		class IsAbove {
		public:
			IsAbove(int& th) : th{ th } {}
			// The only member function
			auto operator()(int v) const { 
				// it is still considered const is that we do not mutate anything inside the actual class / lambda;
				//the actual mutation applies to the referenced value, and therefore the function is still considered const
				return v > th;
			}
		private:
			int& th; // Members
		};
		auto is_above = IsAbove{ th };
		auto test = is_above(5);
	}
}

void TestLambda3() {
	{
		auto func = [c = std::list<int>{ 4,2 }](){
			for (auto v : c)
				std::cout << v;
		};
		func();
	}

	// equivalent code is
	{
		class Func {
		public:
			Func() : c{ 4, 2 } {}
			auto operator()()const->void {
				for (auto v : c)
					std::cout << v;
			}
		private:
			std::list<int> c;
		};
		auto func = Func{};
		func();
	}

}

//Assigning C function pointers to lambdas
//Note that the lambda cannot have any captures at all in order to use this functionality.
void download_webpage(
	const char* url, void(*callback)(int, const char*)) {

}

void testLambda4() {
	// auto lambda = +[](int result, const char* str) {};
		auto lambda = [](int result, const char* str) {};
		download_webpage("http://www.packt.com", lambda);
}


// replace operator new and delete to log allocations
void* operator new(std::size_t n) {
	void* parent = (void*)malloc(n);
	cout << "Allocating " << n << " bytes, " << parent << endl; 
	return parent;
}
void operator delete(void* parent) throw() {
	cout << "Deallocating " << parent << endl;
	free(parent);
}

void testFunction() {
	std::array<char, 32> arr1;
	auto lambda1 = [arr1]() {};
	cout << "Assigning lambda1 of size " << sizeof(lambda1) << endl;
	std::function<void()> f1 = lambda1;

	std::array<char, 33> arr2;
	auto lambda2 = [arr2]() {};
	cout << "Assigning lambda2 of size " << sizeof(lambda2) << endl;
	std::function<void()> f2 = lambda2;
}


void TestLamdaFunction()
{
	testFunction();
}