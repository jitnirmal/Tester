#pragma once
#include <atomic>
#include <thread>

class Spinlock {
	typedef enum { Locked, Unlocked } LockState;
	std::atomic<LockState> state_;
public:
	Spinlock() : state_(Unlocked) {}

	void lock() {
		while (state_.exchange(Locked, std::memory_order_acquire) == Locked) {
			/* busy-wait */
		}
	}

	void unlock() {
		state_.store(Unlocked, std::memory_order_release);
	}
};

Spinlock spin;

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
