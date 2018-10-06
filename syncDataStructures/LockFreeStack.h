
#pragma once
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
#include "ObjectPool.h"

/// <summary>
/// enable maximum concurrency. some thread makes progress with every step.With a wait - free data structure, every thread can make
///            forward progress, regardless of what the other threads are doing
/// If a thread dies while holding a lock, that data structure is broken forever.But if a thread dies partway through an operation on a 
///				lock - free data structure, nothing is lost except that thread’s data; other threads can proceed normally
/// Because there aren’t any locks, deadlocks are impossible with lock-free data structures
///	Livelock : live lock occurs when two threads each try to change the data structure, but for each thread the changes made
///			by the other require the operation to be restarted, so both threads loop and try again.
/// By definition, wait-free code can’t suffer from live lock because there’s always an upper limit on the number 
///			of steps needed to perform an operation.The flip side here is that the algorithm is  likely more complex 
///			than the alternative and may require more steps even when no other thread is accessing the data structure.
/// Disadvantages:
///		you must use atomic operations and pay attention to the ordering constraints you impose on the operations
///		while waiting time is reduced, but overall performance may decrease
///				1. the atomic operations used for lock-free code can be much slower
///				2. the cache ping-pong associated with multiple threads accessing the same atomic variables can be a significant performance drain
///				3. overall algoirigth conditions may increase that decrease the performance
/// 
/// </summary>


template<typename T>
struct Node
{
	Node(const T& dt) :
		data(dt),
		next(nullptr)
	{}
	T data;
	Node* next;
};

template<typename T>
class WaitFree
{
public:
	using NodePtr = Node<T>*;
	WaitFree():_mpSL(500)
	{
		_head.store(nullptr, std::memory_order_release);

	}
	void push(const T& data)
	{
		//auto node = _mpSL.allocate();
		NodePtr Node = new Node<T>(data);
		NodePtr staleHead = _head.load(std::memory_order_relaxed);
		do {
			Node->next = staleHead;
		} while (!_head.compare_exchange_weak(staleHead, Node, std::memory_order_release));
	}
	NodePtr pop_all()
	{
		NodePtr list = pop_all_reverse();
		return reverseList(list);
	}

	NodePtr pop_all_reverse()
	{
		return _head.exchange(nullptr, std::memory_order_consume);
	}

	NodePtr pop()
	{
		NodePtr old_head = head.load();
		while (!head.compare_exchange_weak(old_head, old_head->next));
		return old_head;
	}

private:
	std::atomic<NodePtr> _head;
};