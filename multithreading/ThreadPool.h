#pragma once

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <atomic>

template<typename Data>
class thread_safe_queue {
private:
	std::queue<Data>            _queue;
	std::mutex					_mutex;
	const size_t                _limit;

	std::condition_variable		_signal;
	using queue_lock = std::unique_lock<std::mutex>;
	std::atomic_bool done;

public:
	thread_safe_queue(size_t size_limit = 10)
		: _limit(size_limit), _done(false)
	{}

	void StopQueue()
	{
		_done = true;
		_signal.notify_all();
	}

	bool push(const Data& data)
	{
		if (_done)
		{
			return false;
		}
		queue_lock lock(_mutex);
		_queue.push(data);
		if (_queue.size() == 1) {
			_signal.notify_one();
		}
		return true;
	}

	bool pop(Data &popped_value)
	{
		queue_lock lock(_mutex);
		while (_queue.size()==0) {
			if (_done == true)
			{
				return false;
			}
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

		_signal.notify_one();
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


class join_threads
{
	std::vector<std::thread>& threads;
public:
	explicit join_threads(std::vector<std::thread>& threads_) :
		threads(threads_)
	{}
	~join_threads()
	{
		for (unsigned long i = 0; i<threads.size(); ++i)
		{
			if (threads[i].joinable())
				threads[i].join();
		}
	}
};
class thread_pool
{
	std::atomic_bool done;
	thread_safe_queue<std::function<void()> > work_queue;
	std::vector<std::thread> threads;
	join_threads joiner;

	void worker_thread()
	{
		while (!done)
		{
			std::function<void()> task;
			if (work_queue.pop(task))
			{
				task();
			}
			else
			{
				//std::this_thread::yield();
			}
		}
	}
public:
	thread_pool() :
		done(false), joiner(threads)
	{
		unsigned const thread_count = std::thread::hardware_concurrency();
		try
		{
			for (unsigned i = 0; i<thread_count; ++i)
			{
				threads.push_back(
					std::thread(&thread_pool::worker_thread, this));
			}
		}
		catch (...)
		{
			done = true;
			throw;
		}
	}

	~thread_pool()
	{
		done = true;
	}

	template<typename FunctionType>
	void submit(FunctionType f)
	{
		work_queue.push(std::function<void()>(f));
	}
};

void TestThreadPool()
{
	
}