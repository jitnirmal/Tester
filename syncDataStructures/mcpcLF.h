#pragma once
#include <deque>
#include <thread>
#include <mutex>
#include "SpinLock.h"
//https://github.com/rigtorp/MPMCQueue
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
		while(true)
		{
			node = &buffer_[pos & buffer_mask_];
			size_t seq = node->sequence_.load(std::memory_order_acquire);
			intptr_t dif = (intptr_t)seq - (intptr_t)pos;
			if (dif == 0)
			{
				// 1. mark the buffer for writing index
				if (head_.compare_exchange_weak	(pos, pos + 1, std::memory_order_relaxed))
					break;
			}
			else if (dif < 0)
			{
				//2.
				return false;
			}
			else
			{
				//3.  this index is already used by another thread
				pos = head_.load(std::memory_order_relaxed);
			}
		}
		//update the record one 1 is successful
		node->data_ = data;
		node->sequence_.store(pos + 1, std::memory_order_release);
		return true;
	}

	bool dequeue(T& data)
	{
		Node* node(nullptr);
		size_t pos = tail_.load(std::memory_order_relaxed);
		while(true)
		{
			node = &buffer_[pos & buffer_mask_];
			size_t seq = node->sequence_.load(std::memory_order_acquire);

			intptr_t dif = (intptr_t)seq - (intptr_t)(pos + 1);
			if (dif == 0)
			{
				// 1. mark the buffer for reading index 
				if (tail_.compare_exchange_weak (pos, pos + 1, std::memory_order_relaxed))
					break;
			}
			else if (dif < 0)
			{
				//nothing to be read
				return false;
			}
			else
			{
				//3. this index is already read by another thread
				pos = tail_.load(std::memory_order_relaxed);
			}
		}
		data = node->data_;
		node->sequence_.store(pos + buffer_mask_ + 1, std::memory_order_release);
		return true;
	}

private:
	struct Node
	{
		std::atomic<size_t>   sequence_;
		T                     data_;
	};

	static const size_t     cacheline_size = 64;
	typedef char            cacheline_pad_t[cacheline_size];

	cacheline_pad_t         pad0_;
	const Node* 			buffer_;
	const size_t			buffer_mask_;
	
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