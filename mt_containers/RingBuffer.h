#pragma once
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>

template<typename T, size_t Size=500>
class ringbuffer {
public:
	ringbuffer() : _head(0), _tail(0) {}

	bool push(const T & value)
	{
		size_t head = _head.load(std::memory_order_relaxed);
		size_t next_head = next(head);
		if (next_head == _tail.load(std::memory_order_acquire))
			return false;

		ring_[head] = value;
		_head.store(next_head, std::memory_order_release);
		return true;
	}

	bool pop(T & value)
	{
		size_t tail = _tail.load(std::memory_order_relaxed);
		if (tail == _head.load(std::memory_order_acquire))
			return false;
		value = ring_[tail];
		_tail.store(next(tail), std::memory_order_release);
		return true;
	}

private:
	size_t next(size_t current)
	{
		return (current + 1) % Size;
	}

	T ring_[Size];
	std::atomic<size_t> _head;
	std::atomic<size_t> _tail;
};



auto produceR = [](const int producerId, const int numOfEvents, ringbuffer<EventT*>& queue) {
	std::vector<EventT*> vi;
	vi.reserve(numOfEvents);

	for (auto i = 0; i < numOfEvents; ++i) {
		vi.emplace_back(new EventT());
	}
	auto start = std::chrono::steady_clock::now();
	for (const auto& it : vi) {
		//it->begin = std::chrono::steady_clock::now();
		queue.push(it);
	}
	auto end = std::chrono::steady_clock::now();
	std::cout << "ringbuffer Time took = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / numOfEvents << " nano" << std::endl;
	//print(i, producerId,"producer");

};

auto consumeR = [](const int consumerId, ringbuffer<EventT*>& queue) {
	auto count{ 0 };
	while (true) {

		EventT* evt;
		queue.pop(evt);
		++count;
		//print(count, consumerId, "consumer");
	}
};

void TestRingBuffer()
{
	const auto numOfEvents = 1000000;
	const auto producerCount = 1;
	const auto consumerCount = 3;

	ringbuffer<EventT*> queue;
	std::vector<std::thread> producerThreads;
	std::vector<std::thread> consumerThreads;
	for (auto count = 0; count < producerCount; ++count)
	{
		auto producerId = (count + 1) * 100000;
		std::thread producer(produceR, producerId, numOfEvents, std::ref(queue));
		producerThreads.emplace_back(std::move(producer));
	}

	for (auto count = 0; count < consumerCount; ++count)
	{
		auto consumerId = (count + 5) * 100000;
		std::thread consumer(consumeR, consumerId, std::ref(queue));
		consumerThreads.emplace_back(std::move(consumer));
	}

	for (auto& producer : producerThreads)
	{
		producer.join();
	}
	for (auto& consumer : consumerThreads)
	{
		consumer.join();
	}
}
