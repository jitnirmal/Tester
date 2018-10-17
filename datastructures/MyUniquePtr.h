#pragma once
#include <algorithm>
#include <iostream>
/*
	Autoptr is depreciated as it takes ownership of the pointer in a way that no two pointers should contain the same object. Assignment transfers ownership and resets the 
	rvalue auto pointer	to a null pointer. Thus, they can’t be used within STL containers due to the inability to be copied.
	
	unique_ptr is a new facility with a similar functionality, but with 
		- improved security (any attempt to make a copy of unique_ptr will cause a compile time error.)
		- added features (deleters) 
		- support for arrays. 
		It explicitly prevents copying of its contained pointer as would happen with normal assignment i.e. it allows exactly one owner of the underlying pointer.
		- unique_ptr can be moved using the new move semantics i.e. using std::move() function to transfer ownership of the contained pointer to another unique_ptr.
*/

template<class T> 
class m_unique_ptr 
{


public:
	explicit m_unique_ptr(T * p = 0) noexcept : _ptr(p) {}
	
	m_unique_ptr(void) noexcept : _ptr(nullptr) { }

	// disable copy and assignment
	m_unique_ptr(m_unique_ptr const &) = delete;
	m_unique_ptr& operator=(m_unique_ptr const &) = delete;
	
	

	m_unique_ptr(m_unique_ptr&& rhs) noexcept{
		std::swap(_ptr, rhs._ptr);
		rhs.reset();
	}
	
	m_unique_ptr& operator=(m_unique_ptr&& rhs) noexcept {
		std::swap(_ptr, rhs._ptr);
		rhs.reset();
		return *this;
	}

	~m_unique_ptr() noexcept
	{
		destroy();
	}

	void reset(T * p = 0) noexcept 	{
		if (px != p){
			destroy();
			px = p;
		}
	}

	T& operator*() const noexcept {
		// making function const does not pose any restriction
		// that returned pointer cannot be changed
		return *_ptr;
	}

	T* operator->() const noexcept{
		return _ptr;
	}

	T* get() const noexcept {
		return _ptr;
	}
private:
	inline void destroy(void) noexcept 	{
		delete _ptr;
		_ptr = nullptr;
	}
private:
	T * _ptr;
};


void TestUniquePtr()
{
	using intPtr = m_unique_ptr<int>;
	intPtr mup1(new int);
	*mup1 = 100;
	std::cout << "value1 : " << *mup1 << std::endl;
	std::cout << "value2 : " << *(mup1.get()) << std::endl;
	std::unique_ptr<int> ui = std::make_unique<int>(10);
	//intPtr mup2 = mup1;
	//intPtr mup3(mup1);

}