#pragma once
#include <utility> // for std::swap

class MyString
{
public:
	MyString()
		: data_(new char[1])
	{
		*data_ = '\0';
	}

	MyString(const char* str)
		: data_(new char[strlen(str) + 1])
	{
		strcpy(data_, str);
	}

	MyString(const MyString& rhs)
		: data_(new char[rhs.size() + 1])
	{
		strcpy(data_, rhs.c_str());
	}

	MyString& operator=(MyString rhs)
	{
		swap(rhs);
		return *this;
	}

	MyString& operator=(const MyString& rhs)
	{
		MyString tmp(rhs);
		swap(tmp);
		return *this;
	}

	size_t size() const
	{
		return strlen(data_);
	}

	const char* c_str() const
	{
		return data_;
	}

	void swap(MyString& rhs)
	{
		std::swap(data_, rhs.data_);
	}

	// Implement copy-ctor with delegating constructor in c++11
	MyString(const MyString& rhs)
		: MyString(rhs.data_)
	{}

	// move-ctor
	MyString(MyString&& rhs) noexcept
		: data_(rhs.data_)
	{
		rhs.data_ = nullptr;
	}

	~MyString() noexcept
	{
		delete[] data_;
	}

private:
	char* data_;
};