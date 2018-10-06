#pragma once

#include <atomic>
#include <vector>
#include <chrono>
#include <iostream>
#include <thread>


/// <summary>
///  paging and caching effects 
///   1.  the operating system chunks virtual memory into pages (page size is typically 4K)
///			-- anything from disk to ram is loaded in pages
///			Even if one byte is to be read, it impacts
///				-- Speed : A page fault where the OS has to load the entire page from disk.
///				-- Space : Memory overhead for storing the entire page in memory, even if you only ever touch one byte from the page.
///   2.  the cache hardware further chunks memory into cache lines (typically 64 bytes)
///	  On multicore hardware, if one core writes to a byte of memory, then typically, as part of the hardware's cache coherency protocol, 
///	  that core will automatically (read: invisibly) take an exclusive write lock on that cache line. 
///	   -- This prevents other cores from causing trouble by trying to perform conflicting writes. 
///    -- The sad news is that it also means, well, taking a lock.
///	  3. False sharing arises 
///			a. Two independent variables or objects are too close together.
///		    b. Two node - based containers(lists or trees, for example) interleave in memory, so that the same cache line contains nodes from two containers.
/// 
///		Solutions :
///			a. Keep data that are not used together apart in memory. (Keep them on seperate cache lines)
///				-- Add padding, if necessary; it's a great way to "waste" memory to make your code run faster.
///			b. Keep data that is frequently used together close together in memory. 
///				-- If a thread that uses variable A frequently also needs variable B, try to put A and B in the same cache line
///			c. Keep "hot" (frequently accessed) and "cold" (infrequently accessed) data apart
///				 --- to avoid needlessly loading the "colder" parts
/// </summary>

// example code to demonstrate false sharing..
int x = 0, y = 0;
constexpr int MAX = 1000000;

auto Thread1 = []() {
	for (int i = 0; i < MAX; ++i) {
		// If x and y are on the same cache line, however, only one core can be updating the cache line at a time, 
		// because only one core can have exclusive access at a time—
		//lightweightMutexForXandY.lock();
		++x;
		//lightweightMutexForXandY.unlock();
	}
};

auto Thread2 = []() {
	for (int i = 0; i < MAX; ++i) {
		++y;
	}
};

class CSharedData
{
public:
	CSharedData() : data1(0), data2(0), data3(0) {}
	unsigned int data1; // read write
	unsigned int data2; // read write
	unsigned int data3; // read write
};

class __declspec(align(64)) CSharedData
{
public:
	CSharedData() : data1(0), data2(0), data3(0) {}
	__declspec(align(64))
		unsigned int data1;
	__declspec(align(64))
		unsigned int data2;
	__declspec(align(64))
		unsigned int data3;
};


// C++ (using C++0x alignment syntax)
template<typename T>
struct cache_line_storage {
	[[alignas(CACHE_LINE_SIZE)]] T data;
	char pad[CACHE_LINE_SIZE > sizeof(T)
		? CACHE_LINE_SIZE - sizeof(T)
		: 1];
};

int testAlign()
{

}