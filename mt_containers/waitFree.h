
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

	

private:
	NodePtr reverseList(NodePtr list)
	{
		NodePtr current = list;
		NodePtr next = nullptr;
		NodePtr prev = nullptr;
		while (current != nullptr)
		{
			next = current->next;
			current->next = prev;

			prev = current;
			current = next;
		}
		return prev;
	}
private:
	std::atomic<NodePtr> _head;
	MemoryPool<Object, Spinlock> _mpSL;
};
class EventT
{
public:
	int _EventId;
	std::chrono::steady_clock::time_point begin;
};

auto produceW = [](const int producerId, const int numOfEvents, WaitFree<EventT*>& queue) {
	std::vector<EventT*> vi;
	vi.reserve(numOfEvents);

	for (auto i = 0; i < numOfEvents; ++i) {
		vi.emplace_back(new EventT());
	}
	auto start = std::chrono::steady_clock::now();
	for (const auto& it : vi) {
		queue.push(it);
	}
	auto end = std::chrono::steady_clock::now();
	std::cout << "WaitFree Time took = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / numOfEvents << " nano" << std::endl;
	//print(i, producerId,"producer");

};

auto consumeW = [](const int consumerId, WaitFree<EventT*>& queue) {
	auto count{ 0 };
	while (true) {

		EventT* evt;
		queue.pop_all();
		++count;
		//print(count, consumerId, "consumer");
	}
};

void testWaitFree()
{
	const auto numOfEvents = 1000000;
	const auto producerCount = 1;
	const auto consumerCount = 3;

	WaitFree<EventT*> queue;
	std::vector<std::thread> producerThreads;
	std::vector<std::thread> consumerThreads;
	for (auto count = 0; count < producerCount; ++count)
	{
		auto producerId = (count + 1) * 100000;
		std::thread producer(produceW, producerId, numOfEvents, std::ref(queue));
		producerThreads.emplace_back(std::move(producer));
	}

	for (auto count = 0; count < consumerCount; ++count)
	{
		auto consumerId = (count + 5) * 100000;
		std::thread consumer(consumeW, consumerId, std::ref(queue));
		consumerThreads.emplace_back(std::move(consumer));
	}

	for (auto& producer : producerThreads)
	{
		producer.join();
	}
	for (auto& consumer : consumerThreads)
	{
		consumer.detach();
	}

}

