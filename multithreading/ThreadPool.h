#pragma once

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <atomic>
#include <queue>
#include <unordered_map>

template<typename Data>
class thread_safe_queue {
private:
	std::queue<Data>            _queue;
	std::mutex					_mutex;
	std::condition_variable		_signal;

	using queue_lock = std::unique_lock<std::mutex>;
	std::atomic_bool _stopped;

public:
	thread_safe_queue()
		: _stopped(false)
	{}

	void StopQueue()
	{
		_stopped = true;
		_signal.notify_all();
	}

	bool push(const Data& data)
	{
		if (_stopped)
		{
			return false;
		}

		queue_lock lock(_mutex);
		_queue.push(data);
		if (_queue.size() == 1) {
			_signal.notify_all();
		}
		return true;
	}

	bool pop(Data &popped_value)
	{
		queue_lock lock(_mutex);
		while (_queue.size()==0) {
			if (_stopped == true)
			{
				return false;
			}
			_signal.wait(lock);
		}
		popped_value = _queue.front();
		_queue.pop();
		return true;
	}
	bool empty()
	{
		queue_lock lock(_mutex);
		return _queue.size() == 0;
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
	std::atomic_bool _running;
	thread_safe_queue<std::function<void()> > work_queue;
	std::vector<std::thread> threads;
	join_threads joiner;

	void worker_thread()
	{
		while (_running || work_queue.empty()==false)
		{

			std::function<void()> task;
			if (work_queue.pop(task))
			{
				task();
			}
			else
			{
				std::this_thread::yield();
			}
		}
		std::cout <<"stopping : "<< std::this_thread::get_id() << std::endl;
	}
public:
	thread_pool() :
		_running(true), joiner(threads)
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
			_running = false;
			throw;
		}
	}

	~thread_pool()
	{
		work_queue.StopQueue();
		_running = false;
	}

	template<class Task, class ...Args>
	bool submit(Task&& task, Args&& ... args)
	{
		if (_running) {
			return work_queue.push(std::bind(std::forward<Task>(task), std::forward<Args>(args)...));
		}
		return false;
	}
};


void TestThreadPool()
{
	std::mutex m;
	std::unordered_map<std::thread::id, int> counter;
	auto print = [&](const int i, const double d) {
		std::unique_lock<std::mutex> g(m);
		counter[std::this_thread::get_id()]++;
		//std::cout << std::this_thread::get_id() << " : executing event - "<< i  <<" : " << d<< std::endl;
	};
	{
		thread_pool pool;
		std::cout << "Pool created" << std::endl;
		for (int i = 0; i < 100000; ++i)
		{
			pool.submit(print, i, 3.2f);
		}
	}
	int total = 0;
	for (const auto& it : counter)
	{
		total += it.second;

	}

}