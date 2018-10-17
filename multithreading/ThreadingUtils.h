#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include <iostream>

/// <summary>
/// Thread Optmizations
/// 1. Prefer std::async to std::thread
///		Std thread Cost 
///		a) Direct: 
///				-- OS call to allocate space for thread in table
///				-- allocate memory for the thread’s stack
///				-- initialize the thread’s register set
///				-- schedule the thread to run.
///		Schduling : during new scheduling quantum, there is a delay before it begins to run.
///		b) Indirect :
///				- increase in the amount of memory used.Each thread must reserve storage for its own stack of called functions.
///				If large numbers of threads are started and stopped frequently, this can cause thrashing in the cache as threads
///				 executing on the computer compete for access to a limited cache.
///				- when the number of software threads exceeds the number of hardware threads.All threads then begin to slow down as they
///					must be scheduled by the operating system.
///		Thread takes average 135 ms, while std::aysnc performs about 14 times better
/// 
/// 2. Create as Many Runnable Threads as Cores -std::thread::hardware_concurrency()
/// 3. Implement a Task Queue and Thread Pool
/// Advantages :
///				- efficiently handle I / O completion events from nonblocking I / O calls, achieving high processor utilization.
///				- Having a thread pool and task queue eliminates the overhead of starting threadsfor short - lived tasks.
/// Disadvantages :
///				- inversion of control
/// 4. Perform I/O in a Separate Thread 
/// 5. Avoid the Thundering Herd - many threads are pending on an event, such as the availability of work, that only one thread can service
///			There are enough threads contending for a mutex that many threads pend on the mutex’s operating system signal.
///			When the thread holding the mutex releases it, the event is signaled, and all the pending threads become runnable.
///			The first thread to get the processor locks the mutex again.All the remaining threads eventually get the processor, check the mutex,
///			see it is still locked, and go back to pending.The overall effect is that the operating system spends a lot of time restarting threads,
///			 but most threads don’t progress.
/// 6. Avoid Lock Convoys
///			Repetition of thundering herd.
/// 7. Reduce Contention
///				a. Fine-grained locking -  global vs record level locks
///				b. Lock-free data structures
///				c. Duplicate resources - copy objects
///				d. Partition resources
/// 8. Limit Producer Output Queue Length
///				a. The producer contends for the processor, memory allocator, and other resources,
///						further slowing the consumer and exacerbating the problem.
///				b. The producer will eventually consume all system memory resources, causing the 
///						entire program to terminate unexpectedly.
///				c. If the program is designed to recover from exceptions, it may need to process all
///					queued data before restarting, which increases the time to recover.
/// 9. Libraries
///			a. Boost.Thread and Boost.Coroutine
///			b. POSIX Threads
///			c. Threading Building Blocks (TBB) - now open source
///					- parallel for loops
///					- tasks and thread pools
///					- concurrent containers
///					- data - flow message - passing classes, and synchronization primitives
///			d. 0mq / MPI
///			e. OpenMP
/// 
/// </summary>

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
/// Key notes
///		1. Promises and futures can’t be copied.They can be constructed and move-constructed
///		2. If the thread attempts to set a value or exception more than once, the shared state
///			is instead set to the exception std::future_error with an error code of promise_already_satisfied,
///			 and the shared state becomes ready releasing any futures waiting on the promise.
///		3. If the thread never sets a value or exception, when the promise is destroyed, the
///			destructor sets the shared state to the exception std::future_error with error
///			code broken_promise, and the shared state becomes ready, releasing any futures waiting on the promise.
///			To get this useful error indication, the promise must be destroyed in the thread’s callable object.
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
	try {
		std::cout << f.get() << '\n';
	}
	catch (std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}
}

/// <summary>
/// The std::packaged_task template class wraps any callable object(which can be a function pointer, function object, lambda, or bind expression)
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