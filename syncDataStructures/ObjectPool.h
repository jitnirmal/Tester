#pragma once
#include <deque>
#include <thread>
#include <mutex>
#include "SpinLock.h"

/// <summary>
/// C++ memory manager defaults to std::allocator, which calls::operator new() and ::operator delete(),
/// ::operator new() and ::operator delete() have a very complex and difficult job, 
///		-- allocating storage for all type of big and small objects, 
///		-- for single - and multithreaded programs.
/// Their design is a compromise to achieve such generality.Sometimes, a more specialized allocator can do a better job.
/// Thus, Alloc can be specified as something other than the default to provide a specialized allocator for user objects.
/// </summary>

template <typename T,typename LockType>
class MemoryPool
{
public:
	using pool_lock = std::unique_lock<LockType>;

	MemoryPool(size_t numOfRecords, bool useLock = true) :
		_useLock(useLock),
		_mLock()
	{
		for (size_t i = 0; i < numOfRecords; ++i)
		{
			auto ptr = new T();
			_freeList.push_back(ptr);
		}

	}

	inline auto allocate()
	{
		auto deallocate=[&](T* ptr)
		{
			if (_useLock) pool_lock lock(_mLock);
			_freeList.push_front(ptr);
		};

		T* ptr = nullptr;
		{
			if(_useLock) pool_lock lock(_mLock);
			if (!_freeList.empty())
			{
				ptr = _freeList.front();
				_freeList.pop_front();
				return std::unique_ptr<T,decltype(deallocate)>(ptr, deallocate);
			}
		}
		ptr = new T();
		return std::unique_ptr<T, decltype(deallocate)>(ptr, deallocate);
	}
private:
	inline void flush()
	{
		for (auto& ptr : _freeList)
		{
			delete ptr;
		}
		_freeList.clear();
	}
private:
	std::deque<T*> _freeList;
	LockType _mLock;
	const bool _useLock;
};

struct Object{
	char buffer[500];
};

template <typename T, typename LockType>
auto testPool(const std::string& type, MemoryPool<T, LockType>& mp)
{
	constexpr int ITERATIONS{ 1000000 };
	{
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < ITERATIONS; ++i)
		{
			auto object = mp.allocate();
	//		mp.deallocate(object);
		}
		auto end = std::chrono::system_clock::now();
		std::cout << "elapsed time: "<<type<<" : " << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)).count() / ITERATIONS << " nano\n";
	}
}

void TestAllocator()
{
	//using LockType = Spinlock;
	//using LockType = std::mutex;

	MemoryPool<Object, spinlock_mutex> mTest(10,false);
	{
		mTest.allocate();
	}

	constexpr int ITERATIONS{ 1000000 };
	MemoryPool<Object, spinlock_mutex> mpSL(10);
	testPool("Spinlock",mpSL);

	MemoryPool<Object, std::mutex> mpML(10);
	testPool("mutex", mpML);

	MemoryPool<Object, spinlock_mutex> mpNL(10, false);
	testPool("Nolock", mpNL);

	{
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < ITERATIONS; ++i)
		{
			auto object = std::make_unique<Object>();
		}
		auto end = std::chrono::system_clock::now();
		std::cout << "elapsed time new/delete : " << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)).count() / ITERATIONS << " nano\n";
	}
	
	
	
}