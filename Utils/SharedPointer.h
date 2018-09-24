#pragma once

class RC
{
private:
	int count; 

public:
	void AddRef() {
		count++;
	}

	int RemRef() {
		return --count;
	}
	bool Empty() {
		return (count == 0);
	}
};

template < typename T > 
class SharedPointer
{
private:
	T * _data;       // pointer
	RC* _refCount; // Reference count

public:
	explict SharedPointer() 
		: _data(nullptr), 
		_refCount(nullptr) 
	{
		_refCount = new RC();
		_refCount->AddRef();
	}

	SharedPointer(T* tPtr) 
		: _data(tPtr),
		_refCount(nullptr) 
	{
		_refCount = new RC();
		_refCount->AddRef();
	}

	SharedPointer(const SharedPointer<T>& sp) 
		: _data(sp._data), 
		_refCount(sp._refCount)
	{
		_refCount->AddRef();
	}

	SharedPointer(SharedPointer<T>&& sp)
		: _data(sp._data),
		_refCount(sp._refCount)
	{
		sp._data = nullptr;
		_refCount._data = nullptr;
	}
	
	void RemoveReference()
	{
		_refCount->RemRef();
		if (_refCount->Empty())
		{
			delete _data;
			_data = nullptr;

			delete _refCount;
			_refCount = nullptr;
		}
	}

	~SharedPointer()
	{
		RemoveReference();
	}

	T& operator* ()
	{
		return *_data;
	}

	T* operator-> ()
	{
		return _data;
	}

	SharedPointer<T>& operator = (const SharedPointer<T>& sp)
	{
		if (this != &sp) // Avoid self assignment
		{
			RemoveReference();
			_data = sp._data;
			_refCount = sp._refCount;
			_refCount->AddRef();
		}
		return *this;
	}

	SharedPointer<T>& operator = (SharedPointer<T>&& sp)
	{
		if (this != &sp) // Avoid self assignment
		{
			_data = sp._data;
			_refCount = sp._refCount;
			sp._data = nullptr;
			_refCount._data = nullptr;
		}
		return *this;
	}
};