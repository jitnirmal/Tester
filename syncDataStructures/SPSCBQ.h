#include <deque>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>

//https://www.boost.org/doc/libs/1_48_0/doc/html/container/non_standard_containers.html
//https://www.boost.org/doc/libs/1_54_0/doc/html/atomic/usage_examples.html



template<typename Data>
class BlockingQ {
private:
	std::deque<Data>*            _queue1;
	std::deque<Data>*            _queue2;
	std::mutex					_mutex;
	
	std::condition_variable		_signalItemAdded;
	using queue_lock = std::unique_lock<std::mutex>;

public:
	BlockingQ() 
		: _queue1(new std::deque<Data>()),
		_queue2(new std::deque<Data>())
	{}
	virtual ~BlockingQ()
	{
		delete _queue1;
		delete _queue2;
	}
	
	void enqueue(const Data& data)
	{
		queue_lock lock(_mutex);
		_queue1->push_back(data);
		if (_queue1->size() == 1){
			_signalItemAdded.notify_one();
		}
	}
	
	void enqueue(Data&& data)
	{
		queue_lock lock(_mutex);
		_queue1->push_back(std::move(data));
		if (_queue1->size() == 1) {
			_signalItemAdded.notify_one();
		}
	}

	Data dequeue()
	{
		if (_queue2->empty())
		{
			queue_lock lock(_mutex);
			while (_queue1.empty() ) {
				_signalItemAdded.wait(lock);
			}
			std::swap(_queue1, _queue2);
		}
		Data t = std::move(_queue2->front());
		_queue2->pop_front();
		return t;
	}
	
	

	bool empty() const
	{
		queue_lock lock(_mutex);
		return (_queue1.empty() && _queue2.empty());
	}

};


/*

class Event
{
public:
Event(const int id)
:_EventId(id) {}
void SetId(const int id) {
_EventId = id;
}
int GetId() {
return _EventId;
}
private:
int _EventId;
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

auto produce = [](const int producerId, const int numOfEvents, BlockingQ<Event*>& queue) {
	for (auto i = 0; i < numOfEvents; ++i) {
		auto event = new Event(producerId+ i);
		queue.enqueue(event);
		print(i, producerId,"producer");
	}
};

auto consume = [](const int consumerId, BlockingQ<Event*>& queue) {
	auto count{ 0 };
	while (true) {
		
		Event* ev = queue.dequeue();
		++count;
		print(count, consumerId, "consumer");
	}
};

void TestBlockingQueue()
{
	const auto numOfEvents = 1000;
	const auto producerCount = 1;
	const auto consumerCount = 1;
	
	BlockingQ<std::shared_ptr<Event>> queue;
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
		consumer.join();
	}

}
*/