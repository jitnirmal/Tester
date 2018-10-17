//https://codereview.stackexchange.com/questions/180058/a-vector-implementation
#pragma once
#include <algorithm>



template <typename T>
class Vector
{
public:
	explicit Vector(int initSize = 0) : _size{ initSize },
		_capacity{ initSize + SPARE_CAPACITY }
	{
		_data = new T[_capacity];
	}

	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> init)
	{
		_size = init.size();
		_capacity = _size + SPARE_CAPACITY;
		_data = new T[_capacity];
		for (int k = 0; k < _size; ++k)
			_data[k] = init[k];
	}

	Vector(const Vector & rhs) : _size{ rhs._size },
		_capacity{ rhs._capacity }, _data{ nullptr }
	{
		_data = new T[_capacity];
		for (int k = 0; k < _size; ++k)
			_data[k] = rhs._data[k];
	}

	Vector(Vector && rhs) : _size{ rhs._size },
		_capacity{ rhs._capacity }, _data{ rhs._data }
	{
		rhs._data = nullptr;
		rhs._size = 0;
		rhs._capacity = 0;
	}


	Vector & operator= (const Vector & rhs)
	{
		if (*this != rhs) {
			Vector copy = rhs;
			std::swap(*this, copy);
		}
		return *this;
	}
	
	Vector & operator= (Vector && rhs)
	{
		std::swap(_size, rhs._size);
		std::swap(_capacity, rhs._capacity);
		std::swap(_data, rhs._data);

		return *this;
	}

	~Vector()
	{
		delete[] _data;
	}

	

	
	void resize(int newSize)
	{
		if (newSize > _capacity)
			reserve(newSize * 2);
		_size = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < _size)
			return;

		T *newArray = new T[newCapacity];
		for (int k = 0; k < _size; ++k)
			newArray[k] = std::move(_data[k]);

		_capacity = newCapacity;
		std::swap(_data, newArray);
		delete[] newArray;
	}

	T& operator[](int index)
	{
		return _data[index];
	}
	const T& operator[](int index) const
	{
		return _data[index];
	}

	bool empty() const
	{
		return size() == 0;
	}
	int size() const
	{
		return _size;
	}
	int capacity() const
	{
		return _capacity;
	}

	void push_back(const T & x)
	{
		if (_size == _capacity)
			reserve(2 * _capacity + 1);
		_data[_size++] = x;
	}

	void push_back(T && x)
	{
		if (_size == _capacity)
			reserve(2 * _capacity + 1);
		_data[_size++] = std::move(x);
	}

	void pop_back()
	{
		--_size;
	}

	const T & back() const
	{
		return _data[_size - 1];
	}

	using iterator = T* ;
	using const_iterator = const T* ;

	iterator begin()
	{
		return &_data[0];
	}
	const_iterator begin() const
	{
		return &_data[0];
	}
	iterator end()
	{
		return &_data[size()];
	}
	const_iterator end() const
	{
		return &_data[size()];
	}

	const int SPARE_CAPACITY = 16;

private:
	int _size;
	int _capacity;
	T* _data;
};