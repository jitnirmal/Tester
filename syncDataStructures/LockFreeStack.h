
#pragma once
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
#include "ObjectPool.h"

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
		NodePtr node = new Node<T>(data);
		NodePtr staleHead = _head.load(std::memory_order_relaxed);
		do {
			node->next = staleHead;
		} while (!_head.compare_exchange_weak(staleHead, node, std::memory_order_release));
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