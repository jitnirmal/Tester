#include <boost/lockfree/spsc_queue.hpp>
#include <thread>
#include <iostream>
#include<atomic>
#include <mutex>
#include <condition_variable>
#include<thread>
#include<queue>
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono_literals;
uint64_t timestamp_now()
{
	return std::chrono::high_resolution_clock::now().time_since_epoch() / std::chrono::microseconds(1);
}

template <typename Data>
class BlockingQueue
{
public:
	BlockingQueue(const size_t size = 100U) noexcept : MAX_SIZE(size) {}
	~BlockingQueue() noexcept {
	}

	void add(const Data& item)
	{
		std::unique_lock<std::mutex> guard(_mutex);
		while (_queue.size() >= MAX_SIZE)
		{
			_itemsRemovedCV.wait(guard);
		}
		_queue.push(item);
		_itemAddedCV.notify_one();
	}

	void remove(Data& data)
	{
		std::unique_lock<std::mutex> guard(_mutex);
		while (_queue.size() == 0)
		{
			_itemAddedCV.wait(guard);
		}
		data = _queue.front();
		_queue.pop();
		_itemsRemovedCV.notify_one();
	}

private:
	std::queue<Data> _queue;
	std::mutex _mutex;
	std::condition_variable _itemAddedCV;
	std::condition_variable _itemsRemovedCV;
	const size_t MAX_SIZE;
};
int testBlockingQueue()
{
	int const numOfRuns = 10;
	long long writeTime(0);
	long long readTime(0);

	for (int run = 0; run < numOfRuns; ++run)
	{
		BlockingQueue<int> queue;
		int const iterations = 1000000;

		std::thread write_thread([&]() {
			uint64_t begin = timestamp_now();
			for (int i = 0; i < iterations; i++)
			{
				queue.add(i);
			}
			uint64_t end = timestamp_now();
			writeTime += (end - begin) * 1000 / iterations;
		}
		);
		std::thread read_thread([&]() {
			uint64_t begin = timestamp_now();
			int data;
			for (int i = 0; i < iterations; i++)
			{
				queue.remove(data);
			}
			uint64_t end = timestamp_now();
			readTime += (end - begin) * 1000 / iterations;
		}  // End of lambda expression
		);
		write_thread.join();
		read_thread.join();
	}


	printf("\tAverage Blocking Queue write Latency = %ld nanoseconds\n", writeTime / numOfRuns);
	printf("\tAverage Blocking Queue read Latency = %ld nanoseconds\n", readTime / numOfRuns);
	return 0;
}

#define RING_BUFFER_SIZE 1000
class lockless_ring_buffer_spsc
{
public:

	lockless_ring_buffer_spsc()
	{
		write.store(0);
		read.store(0);
	}

	bool try_push(int64_t val)
	{
		const auto current_tail = write.load();
		const auto next_tail = increment(current_tail);
		if (next_tail != read.load())
		{
			buffer[current_tail] = val;
			write.store(next_tail);
			return true;
		}

		return false;
	}

	void push(int64_t val)
	{
		while (!try_push(val));
	}

	bool try_pop(int64_t* pval)
	{
		auto currentHead = read.load();

		if (currentHead == write.load())
		{
			return false;
		}

		*pval = buffer[currentHead];
		read.store(increment(currentHead));

		return true;
	}

	int64_t pop()
	{
		int64_t ret;
		while (!try_pop(&ret));
		return ret;
	}

private:
	std::atomic<int64_t> write;
	std::atomic<int64_t> read;
	int64_t size = RING_BUFFER_SIZE;
	int64_t buffer[RING_BUFFER_SIZE];

	int64_t increment(int n)
	{
		return (n + 1) % size;
	}
};



int testLockFreeRingBuffer()
{
	int const numOfRuns = 10;
	long long writeTime(0);
	long long readTime(0);

	for (int run = 0; run < numOfRuns; ++run)
	{
		lockless_ring_buffer_spsc queue;
		int const iterations = 1000000;

		std::thread write_thread([&]() {
			uint64_t begin = timestamp_now();
			for (int i = 0; i < iterations; i++)
			{
				queue.push(i);
			}
			uint64_t end = timestamp_now();
			writeTime += (end - begin) * 1000 / iterations;
		}
		);
		std::thread read_thread([&]() {
			uint64_t begin = timestamp_now();
			for (int i = 0; i < iterations; i++)
			{
				queue.pop();
			}
			uint64_t end = timestamp_now();
			readTime += (end - begin) * 1000 / iterations;
		}  // End of lambda expression
		);
		write_thread.join();
		read_thread.join();
	}
	
	
	printf("\tAverage LockLess write Latency = %ld nanoseconds\n", writeTime/ numOfRuns);
	printf("\tAverage LockLess read Latency = %ld nanoseconds\n", readTime/ numOfRuns);
	return 0;
}
void testLockFree()
{

	boost::lockfree::spsc_queue<int> q{ 100 };
	int sum = 0;

	auto produce = [&]()
	{
		for (int i = 1; i <= 100; ++i)
			q.push(i);
	};

	auto consume=[&]()
	{
		int i;
		while (q.pop(i))
			sum += i;
	};

	std::thread t1{ produce };
	std::thread t2{ consume };

	t1.join();
	t2.join();
	std::cout << sum << '\n';
}

void testThreadCoordination()
{
	mutex m;
	int x = 0;
	int y = 0;
	
	auto first = [&]()
	{
		while (true)
		{
			m.lock();
			x = 1;
			y = 1;
			m.unlock();

			std::this_thread::sleep_for(1ms);
		}
	};

	auto second = [&]()
	{
		int good(0);
		int bad(0);
		while (true)
		{
			m.lock();
			if (y == 1)
			{
				if (x != 1)
				{
					++bad;
					std::cout << "reording issue happened : " << bad << " , ok : "<<good<< "\n";
				}
				else
				{
					++good;
					if (good % 1000 == 0)
					{
						std::cout << "looks good : " << bad << " , ok : " << good << "\n";
					}
				}
			}
			x = 0;
			y = 0;
			m.unlock();
			std::this_thread::sleep_for(1ms);

		}
	};

	std::thread t1{ first };
	std::thread t2{ second };

	t1.join();
	t2.join();
}


void testAtomicThreadCoordination()
{
	atomic<int> a(0);
	int x = 0;
	int y = 0;

	auto first = [&]()
	{
		while (true)
		{
			x = 1;
			y = 1;
			a.fetch_add(1, memory_order_release);

			std::this_thread::sleep_for(1ms);
		}
	};

	auto second = [&]()
	{
		int good(0);
		int bad(0);
		while (true)
		{
			int tmp = a.load(memory_order_acquire);
			if (tmp == 1) {
				if (y == 1)
				{
					if (x != 1)
					{
						++bad;
						std::cout << "reording issue happened : " << bad << " , ok : " << good << "\n";
					}
					else
					{
						++good;
						if (good % 1000 == 0)
						{
							std::cout << "looks good : " << bad << " , ok : " << good << "\n";
						}
					}
				}
				x = 0;
				y = 0;
				std::this_thread::sleep_for(1ms);
			}
			else
			{

			}


		}
	};

	std::thread t1{ first };
	std::thread t2{ second };

	t1.join();
	t2.join();
}

void testThreadCreation()
{
	int const iterations = 1;
	uint64_t begin = timestamp_now();
	for (int i = 0; i < iterations; ++i)
	{
		std::thread t([&]() {return i; });
		t.join();
	}
	uint64_t end = timestamp_now();
	long int avg_latency = (end - begin) * 1000 / iterations;
	printf("\tAverage NanoLog Latency = %ld nanoseconds\n", avg_latency);
}