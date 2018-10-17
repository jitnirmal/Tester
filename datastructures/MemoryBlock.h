// MemoryBlock.h  
#pragma once  
#include <iostream>  
#include <algorithm>  

class MemoryBlock
{
public:

	explicit MemoryBlock(size_t length)
		: _length(length)
		, _data(new int[length])
	{
	}

	~MemoryBlock()
	{
		if (_data != nullptr)
		{
			delete[] _data;
		}
	}

	MemoryBlock(const MemoryBlock& other)
		: _length(other._length)
		, _data(new int[other._length])
	{
		std::copy(other._data, other._data + _length, _data);
	}

	MemoryBlock& operator=(const MemoryBlock& other)
	{
		if (this != &other)
		{
			auto origPtr = _data;
			_length = other._length;
			_data = new int[_length];
			std::copy(other._data, other._data + _length, _data);
			delete[] origPtr;
		}
		return *this;
	}

	MemoryBlock(MemoryBlock&& other)
		: _data(nullptr)
		, _length(0)
	{
		_data = other._data;
		_length = other._length;

		other._data = nullptr;
		other._length = 0;
	}

	MemoryBlock& operator=(MemoryBlock&& other)
	{
		if (this != &other)
		{
			delete[] _data;

			_data = other._data;
			_length = other._length;
			other._data = nullptr;
			other._length = 0;
		}
		return *this;
	}

	size_t Length() const
	{
		return _length;
	}

private:
	size_t _length; // The length of the resource.  
	int* _data; // The resource.  
};

void testMemoryBlock()
{
	MemoryBlock memBlock100(100); //default constructor
	MemoryBlock memBlock200(200); //default constructor

	MemoryBlock memBlock1(memBlock100); //copy constructor
	MemoryBlock memBlock2(std::move(memBlock100)); //move constructor
	
	memBlock1 = memBlock200;  //copy assignment
	memBlock2 = std::move(memBlock200); //move assignment
}