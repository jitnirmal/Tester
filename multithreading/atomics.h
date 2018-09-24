#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include <iostream>

/// <summary>
/// Sequential consistency is a consistency model that requires on multiprocessor system, 
/// -- all instructions are executed in some order 
/// -- all writes become instantly visible throughout the system
/// 
/// memory_order_relaxed
///		-- no synchronization or ordering constraints
///     -- only atomicity is required from this operation
/// memory_order_consume
///     -- no reads or writes in the current thread that are dependent on the value currently loaded can be reordered 
///			before this load operation.
///		-- Writes to data dependent variables in other threads that release the same atomic variable are visible in the current thread
/// memory_order_acquire (load operation)
///     -- performs the acquire operation on the affected memory location
///     -- no reads or writes in the current thread can be reordered before this load.
///		-- All writes in other threads that release the same atomic variable are visible in the current thread
/// memory_order_release (store operation)
///     -- performs the release operation on the affected memory location
///     -- no reads or writes in the current thread can be reordered after this store.
///		-- All writes in current threads are visible in other threads that aquire the same atomic variable 
///     -- writes that carry a dependency to the atomic variable become visible in other threads that consume the same atomic.
/// memory_order_acq_rel
///		-- read-modify-write operation (both aquire and release
///     -- No memory reads or writes in the current thread can be reordered before or after this store
/// memory_order_seq_cst
///     -- both an acquire operation and a release operation
///     -- a single total order exists in which all threads observe all modifications in the same order.
/// </summary>

template <typename T, typename I = typename std::enable_if<std::is_integral<T>::value>::type>
class atomic_counter
{
	std::atomic<T> counter{ 0 };
public:
	T increment()
	{
		return counter.fetch_add(1);
	}
	T decrement()
	{
		return counter.fetch_sub(1);
	}
	T get()
	{
		return counter.load();
	}
};

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

void TestAtomics()
{
	TestLockFreeAtomic();
	atomic_counter<int> ctrInt;
	atomic_counter<char> ctrStr;

}