#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>

/// <summary>
/// Thread-Safe Initialization of Data
///		1. Constant expressions
///			 -- expressions which the compiler can initialize during compile time. they are implicit thread safe. 
///				constexpr double pi=3.14; 
///			--	user defined types can also be constant expressions if
///					a) They must not have virtual methods or a virtual base class.
///					b) Their constructor must be empty and itself be a constant expression.
///					c) Their methods, which can be callable at compile time, must be constant expressions.
/// </summary>

struct MyDouble {
	constexpr MyDouble(double v) : val(v) {}
	constexpr double getValue() { return val; }
private:
	double val;
};
void testConstExprObject() {
	constexpr MyDouble myDouble(10.5);
	//std::cout << myDouble.getValue() << std::endl;
}

/// <summary>
/// The function call_once in combination with the once_flag
/// </summary>
/// 
std::once_flag onceFlag;
void do_once(){
std::call_once(onceFlag, []() { std::cout << "Only once." << std::endl; });
}


/// <summary>
/// 
/// </summary>

class X {
public:
	static X * instance()
	{
		X * tmp = instance_.load(std::memory_order_consume);
		if (!tmp) {
			std::lock_guard<std::mutex> guard(instantiation_mutex);
			tmp = instance_.load(std::memory_order_consume);
			if (!tmp) {
				tmp = new X;
				instance_.store(tmp, std::memory_order_release);
			}
		}
		return tmp;
	}
private:
	static std::atomic<X*> instance_;
	static std::mutex instantiation_mutex;
};



void TestCallOnce() {

	std::cout << std::endl;
	std::thread t1(do_once);
	std::thread t2(do_once);
	std::thread t3(do_once);
	std::thread t4(do_once);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << std::endl;
}

/// <summary>
/// Static variables with block scope
/// </summary>
void TestThreadSafe()
{

}