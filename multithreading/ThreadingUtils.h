#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include <iostream>




void func(int& x)
{
	try {
		int count{ 0 };
		while (true)
		{
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(1s);
			auto id = std::this_thread::get_id();
			std::cout << "executing thread " << id << " : " << x << std::endl;
			++count;
			if (count == 5)
			{
				throw std::runtime_error("error");
			}
		}
	}
	catch (...)
	{
		std::cout << " unknown error thrown " << std::endl;
	}
}

void TestThread()
{
	auto x = 20;
	//std::thread t;

	// initializing thread with outside function
	std::thread t1(func, std::ref(x));

	// initializing thread with lambda function....
	/*std::thread t2([&]() {
	while (true)
	{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(1s);
	auto id = std::this_thread::get_id();
	std::cout << "executing thread " << id << " : " << x << std::endl;
	}
	});*/

	t1.join();
	//t2.join();
}

class Object {
public:
	Object(int data) :Data(data) {}
public:
	int Data;
};

/// <summary>
/// The promise-future pair is basically a communication channel that enables a thread to 
/// communicate a value or exception with another thread through a shared state.
/// set_value() or set_value_at_thread_exit()
/// 
/// Call set_value() on the premise to set the result to represent a value or 
/// set_exception() to set the result to indicate an exception 
/// </summary>
void TestFuturePromise()
{
	auto accumulate = [](std::promise<int> &p)
	{
		try {
			int sum = 0;
			for (int i = 0; i < 5; ++i)
				sum += i;
			p.set_value(sum);
		}
		catch (...)
		{
			p.set_exception(std::current_exception());
		}
	//	p.set_value_at_thread_exit(sum);
	};

	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::thread t{ accumulate, std::ref(p) };
	std::cout << f.get() << '\n';
}

/// <summary>
/// f.get() blocks the calling thread until the value from the shared state is being made available.
/// The future class methods for blocking the thread until the result from the shared state is made available :
///  --- wait() only returns when the result is available.
///  --- wait_for() returns either when the result is available or when the specified timeout expires.
///  --- wait_until() returns either when the result is available or when the specified time point is reached.
/// 
///  If an exception is set to the promise value, calling the get() method on the future will throw this exception.
/// /// </summary>
void TestFutureTask()
{
	//https://theboostcpplibraries.com/boost.thread-futures-and-promises
	auto accumulate = []()
	{
		int sum = 0;
		for (int i = 0; i < 5; ++i)
			sum += i;
		return sum;
	};

	std::packaged_task<int()> task(accumulate);
	std::future<int> f = task.get_future();
	std::thread t{ std::move(task) };
	try {
		std::cout << f.get() << '\n';
	}
	catch (std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}
}

/// <summary>
/// std::async() is a variadic function template that has two overloads: one that specifies a 
/// launch policy as the first argument and another that does not.The other arguments to 
/// std::async() are the function to execute and its arguments, if any.The launch policy is 
/// defined by a scoped enumeration called std::launch (async, defered)
///  ---- async    : a new thread is launched to execute the task asynchronously.
///  ---- deferred : the task is executed on the calling thread 
///  ---- (std::launch::async | std::launch::deferred) - specify both to leave it to implementation
/// 
/// Both the overloads of std::async() return a future object that refers to the shared state
/// created internally by std::async() for the promise - future channel it establishes
/// /// </summary>
void TestAsync()
{
	auto accumulate = []()
	{
		int sum = 0;
		for (int i = 0; i < 5; ++i)
			sum += i;
		return sum;
	};

	std::future<int> f = std::async(accumulate);
	std::cout << f.get() << '\n';

	// alternative
	while (true)
	{
		using namespace std::chrono_literals;
		auto status = f.wait_for(500ms);
		if (status == std::future_status::ready)
			break;
		std::cout << "waiting..." << std::endl;
	}

}

void TestAtomic()
{
	std::atomic<int> atomicInt = 0;
	auto atomicAccess = [&]()
	{
		for (int i = 0; i < 10000; ++i)
		{
			++atomicInt;
		}
	};



	std::thread t1(atomicAccess);
	std::thread t2(atomicAccess);
	t1.join();
	t2.join();
}

void TestLockFreeAtomic()
{
	std::atomic<bool> atomicBool = false;
	std::atomic<char> atomicChar;
	std::atomic<int> atomicInt;
	std::atomic<long> atomicLong;
	std::atomic<long long> atomicLongLong;
	std::atomic<float> atomicFloat;
	std::atomic<double> atomicDouble;
	//	std::atomic<std::string> atomicString;

	std::cout << std::boolalpha;
	std::cout << "atomicBool : " << atomicBool.is_lock_free() << std::endl;
	std::cout << "atomicChar : " << atomicChar.is_lock_free() << std::endl;
	std::cout << "atomicInt : " << atomicInt.is_lock_free() << std::endl;
	std::cout << "atomicLong : " << atomicLong.is_lock_free() << std::endl;
	std::cout << "atomicLongLong : " << atomicLongLong.is_lock_free() << std::endl;
	std::cout << "atomicFloat : " << atomicFloat.is_lock_free() << std::endl;
	std::cout << "atomicDouble : " << atomicDouble.is_lock_free() << std::endl;
	//	std::cout << "atomicString" << atomicString.is_lock_free() << std::endl;

}