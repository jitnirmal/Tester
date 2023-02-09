
#pragma once

#include <memory>

/// <summary>
///  https://blog.csdn.net/ybhou/article/details/12658349
/// </summary>

#include <cstdlib>
#include <new>
#include <type_traits>
#include <cassert>

template <typename T>
T* aligned_malloc(std::size_t count, std::size_t alignment) 
{
    static_assert(std::is_trivial<T>::value, "aligned_malloc can only be used with trivial types");
    static_assert(alignment % alignof(T) == 0, "alignment must be a multiple of alignof(T)");
    void *ptr = nullptr;
    if (posix_memalign(&ptr, alignment, count * sizeof(T))) 
    {
        throw std::bad_alloc();
    }
    return static_cast<T*>(ptr);
}

template <typename T>
void aligned_free(T* ptr) 
{
    free(ptr);
}

void* aligned_malloc(size_t required_bytes, size_t alignment) {

	// original block
	void* p1;

	// aligned block
	void** p2;

	int offset = alignment - 1 + sizeof(void*);
	if ((p1 = (void*)malloc(required_bytes + offset)) == NULL) {
		return NULL;
	}

	auto val = (alignment - 1);

	p2 = (void**)(((size_t)(p1)+offset) & ~(alignment - 1));

	p2[-1] = p1;

	return p2;
}

void aligned_free(void *parent) {
	free(((void**)parent)[-1]);
}

int testMemory()
{
	void* mem = aligned_malloc(100, 128);
	aligned_free(mem);
}
