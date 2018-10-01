#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>


template<typename Data>
class BlockingQueue {
private:
	std::queue<Data>            _queue;
	std::mutex					_mutex;
	const size_t                _limit;

	std::condition_variable		_signalItemAdded;
	std::condition_variable		_signalItemRemoved;
	using queue_lock = std::unique_lock<std::mutex>;

public:
	BlockingQueue(size_t size_limit = 10) 
		: _limit(size_limit)
	{}

	void push(const Data& data)
	{
		queue_lock lock(_mutex);
		while (_queue.size() >= _limit) {
			_signalItemRemoved.wait(lock);
		}
		_queue.push(data);
		lock.unlock();
		_signalItemAdded.notify_one();
	}

	bool pop(Data &popped_value)
	{
		queue_lock lock(_mutex);
		while (_queue.size()==0) {
			_signalItemAdded.wait(lock);
		}
		popped_value = _queue.front();
		_queue.pop();
		_signalItemRemoved.notify_one();
		return true;
	}

	bool try_push(const Data& data)
	{
		queue_lock lock(_mutex);
		if (_queue.size() >= _limit) {
				return false;
		}
		_queue.push(data);
		lock.unlock();

		_signalItemAdded.notify_one();
		return true;
	}
	bool try_pop(Data &popped_value)
	{
		queue_lock lock(_mutex);
		if (_queue.empty()) {
			return false;
		}

		popped_value = _queue.front();
		_queue.pop();
		_signalItemRemoved.notify_one();
		return true;
	}
	
	

	bool empty() const
	{
		queue_lock lock(_mutex);
		return _queue.empty();
	}

	size_t limit() const
	{
		return _limit;
	}

	size_t size() const
	{
		queue_lock lock(queue_mutex);
		return _queue.size();
	}

};


std::mutex printMutex;

auto print = [](const auto& count, const auto& id, const auto& str)
{
	std::unique_lock<std::mutex> lock(printMutex);
	if (count % 100 == 0)
	{
		std::cout << " id : " << id <<" : "<< str << "  : " << count << " events..\n";
	}
};

auto produce = [](const int producerId, const int numOfEvents, BlockingQueue<Event*>& queue) {
	std::vector<Event*> vi;
	vi.reserve(numOfEvents);

	for (auto i = 0; i < numOfEvents; ++i) {
		vi.emplace_back(new Event(i));
	}
	auto start = std::chrono::steady_clock::now();
	for (const auto& it : vi) {
		queue.push(it);
	}
	auto end = std::chrono::steady_clock::now();
	std::cout << "Blocking Queue Time took = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/ numOfEvents << " nano" << std::endl;
		//print(i, producerId,"producer");
	
};

auto consume = [](const int consumerId, BlockingQueue<Event*>& queue) {
	auto count{ 0 };
	while (true) {
		
		Event* evt;
		queue.pop(std::ref(evt));
		++count;
		//print(count, consumerId, "consumer");
	}
};

void TestBlockingQueue()
{
	const auto numOfEvents = 1000000;
	const auto producerCount = 1;
	const auto consumerCount = 3;
	
	BlockingQueue<Event*> queue;
	std::vector<std::thread> producerThreads;
	std::vector<std::thread> consumerThreads;
	for (auto count = 0; count < producerCount; ++count)
	{
		auto producerId = (count + 1) * 100000;
		std::thread producer(produce, producerId, numOfEvents,std::ref(queue));
		producerThreads.emplace_back(std::move(producer));
	}

	for (auto count = 0; count < consumerCount; ++count)
	{
		auto consumerId = (count + 5) * 100000;
		std::thread consumer(consume, consumerId, std::ref(queue));
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