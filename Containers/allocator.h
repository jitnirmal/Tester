#pragma once
#include <unordered_map>
#include <random>
#include <iostream>
#include <queue>
#include <map>
#include <functional>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

template<class T>
struct tAllocator {
	using value_type = T;
	T *allocate(size_t n) {
		printf("allocate %zu\n", n);
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}
	void deallocate(T *p, size_t n) {
		printf("deallocate %zu\n", n);
		::operator delete(static_cast<void *>(p));
	}
};
void TestAllocatorEx() {
	std::vector<int, tAllocator<int>> v;
	v.push_back(42); 
	v.push_back(42); 
	v.push_back(42); 
}

void TestAllocators()
{
	TestAllocatorEx();
}