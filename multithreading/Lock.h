#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include <mutex>
#include <iostream>

/// <summary>
/// Mutexs :The <mutex> header file contains four mutex templates:
/// std::mutex - A simple, relatively efficient mutex, 
///				On Windows, this class tries a busy-wait first, and falls back to operating system calls if it cannot obtain the mutex quickly
///	std::recursive_mutex- A mutex that allows a thread that already holds the mutex to acquire it again, as in a nested function call.
///			This class may be less efficient due to the need to count how many times it is acquired.
/// std::timed_mutex - A mutex that permits a timed attempt to acquire the mutex.
///					The requirement for timed attempts generally requires intervention from the operating system, which significantly 
///					increases the latency of this type of mutex in comparison to std::mutex.
/// std::recursive_timed_mutex - 
///					A mutex that is both timed and recursive, with mustard, ketchup, and secret
///					sauce.This type of mutex is tasty, but expensive
/// C++14 added the <shared_mutex> header file containing support for shared mutexes,
///					also known as reader / writer mutexes.A single thread can lock a shared mutex in an exclusive mode,
///					 in order to atomically update a data structure.Multiple threads can lock a shared mutex in a shared mode to
///					 atomically read a data structure, but it is locked against exclusive access until all readers have released the mutex.
///					The shared mutex may allow more threads to access the data structure without waiting, provided most accesses are for reading.
///	These shared mutexes are available :
///				a. std::shared_timed_mutex : A shared mutex that supports timed and untimed attempts to acquire the mutex.
///				b.std::shared_mutex : A simpler shared mutex, scheduled for inclusion in C++17.
///	Please note reader/writer mutexes lead to starvation of the writer thread unless reads are infrequent, 
///					in which case the value of the reader / writer optimization is negligible.
/// </summary>
/// 


/// <summary>
/// std::lock_guard - A simple RAII lock.During the class’s construction, the program waits for the lock to be acquired, 
///						and it releases the lock on destruction of the lock_guard.
/// std::unique_lock - A general - purpose mutex ownership class that offers RAII locking, deferred locking, timed locking attempts, 
///						transfer of mutex ownership, and use with condition variables.
/// std::shared_lock -  A mutex ownership class for shared(reader / writer) mutexes.It offers all the sophisticated features of std::unique_lock,
///						plus control of shared mutexes.
/// 
/// 
/// 1. std::condition_variable - The most efficient condition variable, this requires the use of std::unique_lock to lock the mutex.
///	2. std::condition_variable_any - A condition variable that can use any BasicLockable lock; that is, any lock offering lock() and unlock() member functions.
///								This condition variable may be less efficient than std::condition_variable.
/// </summary>
/// 
/// Thread Priority : when there are not enough cores(HW threads), high priority thread gets the preference
/// Priority Inversion : Priority inversion occurs when a high-priority task is forced to wait for the release of a shared resource owned by a lower-priority task. 
///	Solutions :
///		A. Priority ceiling protocol : it gives each shared resource (mutex) a predefined priority ceiling. When a task acquires a shared resource, 
///			the task has its priority temporarily raised to the priority ceiling of that resource.The priority ceiling must be higher than the highest
///			 priority of all tasks that can access the resource, thereby ensuring that a task owning a shared resource won't be preempted by any 
///			other task attempting to access the same resource. When the hoisted task releases the resource, the task is returned to its original priority level. 
///			
///		B. Priority inheritance protocol : When a low-priority task acquires a shared resource, the task continues running at its original priority level.
///			 If a high-priority task requests ownership of the shared resource, the low-priority task is hoisted above the requesting task. 
///			The low-priority task can then continue executing its critical section until it releases the resource. Once the resource is released, 
///			the task is dropped back to its original low-priority level, permitting the high-priority task to use the resource it has just acquired
///				 
/// 
template<typename Lock>
class lock_guard {
public:
	explicit lock_guard(Lock& lock) :_lock(lock) {
		_lock.lock();
	}
	
	/// <summary>
	/// Value used as possible argument to the constructor of unique_lock or lock_guard.
	/// unique_lock objects constructed with adopt_lock do not lock the mutex object on construction,
	///  assuming instead that it is already locked by the current thread.
	/// The value is a compile - time constant that carries no state, and is merely used to disambiguate between constructor signatures
	///  adopt_lock_t is an empty class.
	/// </summary>
	lock_guard(M& Mtx, std::adopt_lock_t) : mtx(Mtx){
	}

	~lock_guard(){
		_lock.unlock();
	}
	lock_guard(const lock_guard&) = delete;
	lock_guard& operator=(const lock_guard&) = delete;
private:
	Lock _lock;
};


/// <summary>
/// deadlock avoidance
/// 1. lock by address
/// 2. back off with try lock
/// </summary>

void avoidDeadLockAlog1(std::mutex& m1, std::mutex& m2)
{
	if (&m1<&m2){
		m1.lock();
		m2.lock();
	}
	else{
		m2.lock();
		m1.lock();
	}
}
void avoidDeadLockAlog2(std::mutex& m1, std::mutex& m2)
{
	do
	{
		m1.lock();
		if (m2.try_lock())
		{
			// do the work...
			m2.unlock();
		}
		m1.unlock();
	} while (true);
}


void TestLockGuard()
{
	

}