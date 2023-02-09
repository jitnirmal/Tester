
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

void* aligned_malloc(size_t required_bytes, size_t alignment) {
    void *ptr = NULL;

    // Allocate extra memory to store the offset
    size_t total_size = required_bytes + alignment - 1 + sizeof(size_t);
    void *raw_ptr = malloc(total_size);
    if (!raw_ptr) {
        return NULL;
    }

    // Calculate the aligned pointer by adding the offset
    ptr = (void*) (((size_t) raw_ptr + alignment - 1 + sizeof(size_t)) & ~(alignment - 1));

    // Store the offset for future use
    *(((size_t*) ptr) - 1) = (size_t) ptr - (size_t) raw_ptr;

    return ptr;
}

void aligned_free(void *ptr) {
    // Calculate the raw pointer from the offset
    void *raw_ptr = (void*) ((size_t) ptr - *(((size_t*) ptr) - 1));

    free(raw_ptr);
}

int testMemory()
{
	void* mem = aligned_malloc(100, 128);
	aligned_free(mem);
}
