#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <string>
#include <iostream>
#include <chrono>

template <typename T>
class ThreadedQ {
public:
	ThreadedQ(std::string name) : _name(name), _q1(new std::queue<T*>), _q2(new std::queue<T*>), _done(true) {}

	~ThreadedQ() {
		if (!_done.load()) {
			std::unique_lock<std::mutex> lock(_lock);
			_q1->push(nullptr);
			lock.unlock();
			_cond.notify_one();
			_thread.join();
		}
		delete _q1;
		delete _q2;
	}

	bool Start() {
		if (_done.load()) {
			_thread = std::thread(&ThreadedQ<T>::run, this);
			return true;
		}
		return false;
	}

	bool push(T data) {
		std::unique_lock<std::mutex> lock(_lock);
		_q1->push(new T(data));
		lock.unlock();
		_cond.notify_one();
		return true;
	}

	bool Stop() {
		if (!_done.load()) {
			std::unique_lock<std::mutex> lock(_lock);
			_q1->push(nullptr);
			lock.unlock();
			_cond.notify_one();
			_thread.join();
			return true;
		}
	}

private:

	void run() {
		_done = false;
		try {
			while (1) {
				if (_q2->empty()) {
					std::unique_lock<std::mutex> guard(_lock);
					_cond.wait(guard, [&]() { return !(_q1->empty()); });
					std::swap(_q1, _q2);
				}
				else {
					while (!_q2->empty()) {
						T* data = _q2->front();
						_q2->pop();
/*						if (data == nullptr) {
							goto Exit;
						}
						std::cout << *data << std::endl;
						delete data;*/
					}
					
				}
			}
		}
		catch (...) {
			std::cout << "Caught exception...." << std::endl;
		}
	Exit:
		_done = true;
		std::cout << "Graceful exit...." << std::endl;
	}

private:
	std::string							_name;
	std::queue<T*>* __restrict			_q1;
	std::queue<T*>* __restrict			_q2;
	std::mutex							_lock;
	std::condition_variable				_cond;
	std::thread							_thread;
	std::atomic<bool>					_done;
};
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
void TestThreadedQ()
{
	const int numOfEvents{ 1000000 };
	std::vector<Event*> vi;
	vi.reserve(numOfEvents);

	for (auto i = 0; i < numOfEvents; ++i) {
		vi.emplace_back(new Event(i));
	}
	
	ThreadedQ<Event*> thQ("TestQ");
	thQ.Start();
	auto start = std::chrono::steady_clock::now();
	for (const auto& it : vi) {
		thQ.push(it);
	}
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time took = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / numOfEvents << " nanoseconds" << std::endl;

	int i;
	std::cin >> i;
}