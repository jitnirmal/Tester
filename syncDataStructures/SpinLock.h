#pragma once
#include <atomic>
#include <thread>


/// <summary>
/// This code doesn’t call any blocking functions; lock() just keeps looping until the call to test_and_set() returns false
/// </summary>
class spinlock_mutex
{
	std::atomic_flag flag;
public:
	spinlock_mutex() :
		flag(ATOMIC_FLAG_INIT)
	{}
	void lock()
	{
		while (flag.test_and_set(std::memory_order_acquire));
	}
	void unlock()
	{
		flag.clear(std::memory_order_release);
	}
};

spinlock_mutex spin;

void workOnResource() {
	spin.lock();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	spin.unlock();
}


void testSpinLock() {

	std::thread t(workOnResource);
	std::thread t2(workOnResource);

	t.join();
	t2.join();
}
