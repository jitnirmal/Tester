#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include <iostream>

/// <summary>
/// std::atomic provides a standard mechanism to update an arbitrary data structure, so long as it is copy constructable or move constructable.
///		Any specialization of std::atomic must provide the following functions for any type T :
///			load() - copies the T object out of the std::atomic<T> atomically.
///			store() - copies a T object into the std::atomic<T> atomically.
///			is_lock_free() -returns bool true if all operations defined on this type are implemented without the use of mutual exclusion, as by a single read - modifywrite
///
///		Intel-architecture PCs have a variety of read-modify-write instructions, and the cost of the atomic access
///		 depends on the memory fence, with some fences having no cost at all.
///		-- Atomics generally may be 14 times slower that direct updates
/// 
/// Sequential consistency is a consistency model that requires on multiprocessor system, 
/// -- all instructions are executed in some order 
/// -- all writes become instantly visible throughout the system
/// 
///	 (Note)	The memory fence blocks forward progress until all writes in flight have completed.
///		In reality, only writes to shared locations need be completed, but neither C++ nor x86 - compatible processors have
///		the means to identify this more restrictive set of locations, especially as the set varies from one thread to the next.
/// 
/// memory_order_relaxed
///		-- no synchronization or ordering constraints
///     -- only atomicity is required from this operation
/// memory_order_acquire (load operation) - acquire all work done by other threads.
///     -- no reads or writes in the current thread can be reordered before this load.
///		-- it waits for store operations currently in flight between the processor and main memory to complete
///		-- less expensive than the default full fence.
/// memory_order_consume
///		-- potentially weaker (and faster) form of memory_order_acquire that requires only that the current load 
///			take place before other operations that are data - dependent on it.
///		-- For instance, when a load of a pointer is marked memory_order_consume, subsequent operations that dereference 
///			this pointer won’t be moved before it.
/// memory_order_release (store operation) - release all work done by this thread to this point.
///     -- no reads or writes in the current thread can be reordered after this store.
///		-- it waits for store operations currently in flight within this thread to complete to be visible by other threads 
///		-- less expensive than the default full fence.
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