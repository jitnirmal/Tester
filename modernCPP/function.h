#pragma once
#include <iostream>
#include <iostream>
#include <functional>
#include <array>
#include <cassert>
#include <memory>
//https://shaharmike.com/cpp/naive-std-function/
using namespace std;

/// <summary>
/// auto -- the compiler detects the type of the expression on the right side, and replaces auto with the detected type (with some exception, read comments)
/// </summary>

/// <summary>
/// The signature of a std::function is defined as follows:
///			--- std::function< return_type ( parameter0, parameter1...) > 
///			--- std::function returning nothing and having no parameters is defined like this...
///				 -- auto func = std::function<void(void)>{};
///			--- A std::function returning a bool and having an int and a std::string as parameters is defined like this:
///				-- auto func = std::function<bool(int, std::string)>{};  
/// 
/// Assigning lambdas to std::functions
///			-- every lambda function has its own type, and therefore cannot be assigned to other lambda functions, even if they look exactly the same. 
///			-- std::function can hold any lambda function which has the same signature, that is, it has the same parameters and the same return value
///			-- what is captured by the lambda does not affect its signature, therefore both lambdas with and without captures can be assigned to 
///				the same std::function
/// 
/// Performance implications - 
/// 1)  An std::function cannot be inlined
///			-- The flexible design of  std::function make it nearly impossible for the compiler to inline a function wrapped in a std::function
///				This overhead can have an impact on the performance if small functions wrapped in std::function are being called very frequently
/// 2)  An std::function heap allocates and captures variables
///          -- If a lambda function with captured variables/references is assigned to a std::function
///					the std::function will, in most cases, allocate space on the heap to store the captured variables 
///			-- This means that not only is there a slight performance penalty due to heap allocation and 
///				the execution of std::function but also that it is slower, as heap allocation implies cache misses
/// 3) Calling a std::function is generally a bit slower than executing a lambda as a little more code is involved
/// </summary>


void testLambdaAssignment() {
	// Create an unassigned std::function object 
	auto func = std::function<void(int)>{};

	// Assign a lambda without capture to the std::function object 
	func = [](int v) { std::cout << v; };
	func(12); // Prints 12 

			  // Assign a lambda with capture to the same std::function object 
	auto forty_two = 42;
	func = [forty_two](int v) { std::cout << (v + forty_two); };
	func(12); // Prints 54 
}


template <typename>
class my_function; // no definition

template <typename ReturnValue, typename ... Args>
class my_function<ReturnValue(Args...)> {
public:
	template <typename T>
	my_function& operator=(T t) {
		callable_ = std::make_unique<CallableT<T>>(t);
		return *this;
	}

	ReturnValue operator()(Args... args) const {
		assert(callable_);
		return callable_->Invoke(args...);
	}
private:
	class ICallable {
	public:
		virtual ~ICallable() = default;
		virtual ReturnValue Invoke(Args...) = 0;
	};

	template <typename T>
	class CallableT : public ICallable {
	public:
		CallableT(const T& t)
			: t_(t) {
		}

		~CallableT() override = default;

		ReturnValue Invoke(Args... args) override {
			return t_(args...);
		}

	private:
		T t_;
	};

	std::unique_ptr<ICallable> callable_;
};


void myfunc(int i) {
	cout << "func"<< i << endl;
}

struct functor {
	void operator()(int i) {
		cout << "functor"<< i << endl;
	}
};


template<typename T,typename... Args>
	shared_ptr<T> make_shared(Args&&... args)
{	
	shared_ptr<T> ptr;
	auto tmp_object = new shared_ptr<T>::_object_and_block<T>(args...);
	ptr._obj_ptr = &tmp_object->object;
	ptr._ref_counter = tmp_object;
	return ptr;
}

void TestFunction()
{
	my_function<void(int)> f;
	f = myfunc;
	f(1);
	f = functor();
	f(2);
	f = [](int x) { cout << "lambda " << x << endl; };
	f(3);

	std::function<void(int)> f1 = myfunc;
	auto sptr = std::make_shared<functor>();
}