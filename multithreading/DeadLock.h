#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include <iostream>



template <typename T>
struct container
{
	std::mutex mutex;
	std::vector<T> data;
};


template <typename T>
void move_between_c11(container<T> & c1, container<T> & c2,
	T const value)
{
	std::lock(c1.mutex, c2.mutex);

	std::lock_guard<std::mutex> l1(c1.mutex, std::adopt_lock);
	std::lock_guard<std::mutex> l2(c2.mutex, std::adopt_lock);

	c1.data.erase(
		std::remove(c1.data.begin(), c1.data.end(), value),
		c1.data.end());
	c2.data.push_back(value);
}

template <typename T>
void move_between_c17(container<T> & c1, container<T> & c2,
	T const value)
{
	std::scoped_lock(c1.mutex, c2.mutex);
	c1.data.erase(
		std::remove(c1.data.begin(), c1.data.end(), value),
		c1.data.end());
	c2.data.push_back(value);
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