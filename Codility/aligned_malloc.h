
#pragma once

#include <memory>

/// <summary>
///  https://blog.csdn.net/ybhou/article/details/12658349
/// </summary>

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

void aligned_free(void *p) {
	free(((void**)p)[-1]);
}

int testMemory()
{
	void* mem = aligned_malloc(100, 128);
	aligned_free(mem);
}