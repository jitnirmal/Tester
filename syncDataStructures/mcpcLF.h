#pragma once
#include <deque>
#include <thread>
#include <mutex>
#include "SpinLock.h"

template<typename T>
class mpmc_bounded_queue
{
public:
	mpmc_bounded_queue(size_t buffer_size)
		: buffer_(new Node[buffer_size])
		, buffer_mask_(buffer_size - 1)
	{
		assert((buffer_size >= 2) &&
			((buffer_size & (buffer_size - 1)) == 0));
		for (size_t i = 0; i != buffer_size; i += 1)
			buffer_[i].sequence_.store(i, std::memory_order_relaxed);
		head_.store(0, std::memory_order_relaxed);
		tail_.store(0, std::memory_order_relaxed);
	}

	~mpmc_bounded_queue()
	{
		delete[] buffer_;
	}

	bool enqueue(T const& data)
	{
		Node* node;
		size_t pos = head_.load(std::memory_order_relaxed);
		for (;;)
		{
			node = &buffer_[pos & buffer_mask_];
			size_t seq = node->sequence_.load(std::memory_order_acquire);
			intptr_t dif = (intptr_t)seq - (intptr_t)pos;
			if (dif == 0)
			{
				if (head_.compare_exchange_weak	(pos, pos + 1, std::memory_order_relaxed))
					break;
			}
			else if (dif < 0)
				return false;
			else
				pos = head_.load(std::memory_order_relaxed);
		}
		node->data_ = data;
		node->sequence_.store(pos + 1, std::memory_order_release);
		return true;
	}

	bool dequeue(T& data)
	{
		Node* node;
		size_t pos = tail_.load(std::memory_order_relaxed);
		for (;;)
		{
			node = &buffer_[pos & buffer_mask_];
			size_t seq =
				node->sequence_.load(std::memory_order_acquire);
			intptr_t dif = (intptr_t)seq - (intptr_t)(pos + 1);
			if (dif == 0)
			{
				if (tail_.compare_exchange_weak
				(pos, pos + 1, std::memory_order_relaxed))
					break;
			}
			else if (dif < 0)
				return false;
			else
				pos = tail_.load(std::memory_order_relaxed);
		}
		data = node->data_;
		node->sequence_.store
		(pos + buffer_mask_ + 1, std::memory_order_release);
		return true;
	}

private:
	struct Node
	{
		std::atomic<size_t>   sequence_;
		T                     data_;
	};

	static size_t const     cacheline_size = 64;
	typedef char            cacheline_pad_t[cacheline_size];

	cacheline_pad_t         pad0_;
	Node* const				buffer_;
	size_t const            buffer_mask_;
	cacheline_pad_t         pad1_;
	std::atomic<size_t>     head_;
	cacheline_pad_t         pad2_;
	std::atomic<size_t>     tail_;
	cacheline_pad_t         pad3_;

	mpmc_bounded_queue(mpmc_bounded_queue const&) = delete;
	mpmc_bounded_queue& operator= (mpmc_bounded_queue const&) = delete;
};

void TestMCPC()
{
	
	
	
	
}