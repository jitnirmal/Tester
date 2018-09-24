

#pragma once
#include <memory>
#include <atomic>

/*Use shared_ptr if you want to share ownership of resource.Many shared_ptr can point to single resource.
shared_ptr maintains reference count for this propose.when all shared_ptr’s pointing to resource goes out of scope the resource is destroyed.

*/

class AtomicRefCount {
private:
	std::atomic<int> _rc;
public:
	void add_ref()
	{
		_rc.fetch_add(1, std::memory_order_relaxed);
	}
	
	void rem_ref()
	{
		_rc.fetch_sub(1, std::memory_order_release);
	}
	int get_count() const
	{
		return _rc.load(std::memory_order_relaxed);
	}
};


class RefCount
{
private:
	int _count{ 0 };
public:
	void add_ref()
	{
		++_count;
	}
	int rem_ref()
	{
		return --_count;
	}
	int get_count() const
	{
		return _count;
	}
};

template <typename T>
class smart_ptr
{
private:
	T * _ptr{ nullptr };
	RefCount* _rc{ nullptr };

public:
	smart_ptr(T* object)
		: _ptr{ object }
		, _rc{ new RefCount() }
	{
		_rc->inc();
	}

	virtual ~smart_ptr()
	{
		if (_rc->dec() <= 0){
				
			delete _rc;
			delete _ptr;
			
			_rc = nullptr;
			_ptr = nullptr;
		}
	}
	
	// Copy Constructor
	smart_ptr(const smart_ptr<T>& other)
		: _ptr{ other._ptr }
		, _rc{ other._rc }
	{
		_rc->inc();
	}

	// Move Constructor
	smart_ptr(smart_ptr<T>&& other)
		: _ptr{ other._ptr }
		, _rc{ other._rc }
	{
		other._rc = nullptr;
		other._ptr = nullptr;
	}


	// Overloaded Assignment Operator
	smart_ptr<T>& operator=(const smart_ptr<T>& other){

		if (this != &other)
		{
			_ptr = other._ptr;
			_rc = other._rc;
			_rc->inc();
		}
		return *this;
	}

	// Overloaded Assignment Operator
	smart_ptr<T>& operator=(smart_ptr<T>&& other){

		if (this != &other){
			_ptr = other._ptr;
			_rc = other._rc;

			other._rc = nullptr;
			other._ptr = nullptr;
		}
		return *this;
	}

	void decrement(){
		if (_rc && _rc->dec() == 0)
		{
			delete _rc;
			delete _ptr;
		}
	}

	//Dereference operator
	T& operator*(){
		return *_ptr;
	}

	//Member Access operator
	T* operator->(){
		return _ptr;
	}
};

void testSharedPointer()
{
	std::shared_ptr<int> sp(new int());
}