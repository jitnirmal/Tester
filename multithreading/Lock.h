#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include <mutex>
#include <iostream>

/// <summary>
/// lock
/// </summary>
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


void TestLockGuard()
{
	

}