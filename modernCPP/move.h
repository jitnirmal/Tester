#pragma once  
#include <utility> // std::move<T>
#include <iostream>  
#include <algorithm>  
#include <vector> 

/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-1          STD::MOVE 
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. Move semantics are a key feature that drives the performance improvements of modern C++.
/// 2. They enable moving, rather than copying, resources or , especially, objects which are expensive to copy.
/// 3. It requires that classes implement a move constructor and assignment operator.
/// 4. Move
///		a. represents a performance benefit for objects that are too large to copy(such as a string or container) 
///		b. objects that are not supposed to be copied, unique_ptr pointer, thread, atomic
/// 5. Some classes can be movable not copyable but it does not make much sense for a class to be copyable but not moveable,
/// 6. built-in types (such as bool, int, or double), arrays, or PODs, the move is actually a copy operation.
/// 7. move semantics provide a performance benefit in the context of rvalues, that is, temporary objects.
///              T a;   --> a is lvalue (object with name)
///				 T b = a;  --> b is lvalue
///              T c = a + b; --> c is lvalue but a+b is rvalue (temporary, rvalue represented with &&)
/// 8. Move semantics allow you to take ownership of temporary resources which otherwise will destroyed 
/// 9. On the other hand, lvalues cannot be moved; they are supposed to be copied, as they are supposed to be used afterwards copy/move
/// 10. When a move constructor/assignment operator exists, an rvalue is moved automatically
/// 11. lvalues can also be moved, but this requires an explicit static_cast<T&&> to an rvalue reference with std::move() function
///					Buffer b(200);
///					c.push_back(b); // copy
///					c.push_back(std::move(b)); // move
/// Because std::move does nothing but cast its argument to an rvalue, better name for it might have been rvalue_cast
/// 12. Move requests on const objects are silently transformed into copy operations
///    * std::move not only doesn’t actually move anything, also it doesn’t even guarantee that the object it’s casting will be eligible to be moved.
/// After an object is moved, it must remain in a valid state  but no specific requirement regarding the state 
/// (usually default 0, nullptr, false)
/// </summary>

/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-2          STD::FORWARD 
/// -------------------------------------------------------------------------------------------------------------------------------------
///  1. Perfect forwarding makes it possible to write function templates that take arbitrary arguments and forward them to other functions 
///      such that the target functions receive exactly the same arguments as were passed to the forwarding functions.
///  2. while std::move unconditionally casts its argument to an rvalue std::forward casts its argument to an rvalue only if that 
///		argument is bound to an rvalue
///  3. From pure technical prospect , std::forward can replace std::move, however it compromise clarity, extra typing for standard forward
/// 

/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-2          UNIVERSAL REFERENCE 
/// -------------------------------------------------------------------------------------------------------------------------------------
///  1. If a function template parameter has type T&& for a deduced type T, or if an object is declared using auto&&, the parameter or object 
///        is a universal reference.
///	
/// 		void f(Widget&& param); // rvalue reference
///			Widget&& var1 = Widget(); // rvalue reference
///			auto&& var2 = var1; // not rvalue reference (universal reference)
///			template<typename T> void f(std::vector<T>&& param); // rvalue reference
///			template<typename T> void f(T&& param); // not rvalue reference (universal reference)
/// 
///  2. If the form of the type declaration isn’t precisely type&&, or if type deduction does not occur, type&& denotes an rvalue reference.
///  3. Universal references correspond to rvalue references if they’re initialized with rvalues.They correspond to lvalue references 
///			if they’re initialized with lvalues.
///  4. Use std::move on rvalue references, std::forward on universal references
/// 5.  Never apply std::move or std::forward to local objects if they would otherwise be eligible for the return value optimization.


template<typename T> // template that passes
void logAndProcess(T&& param) // param to process
{
	// log time
	process(std::forward<T>(param));
}

void TestForward()
{
	Clazz c;
	logAndProcess(c); // call with lvalue
	logAndProcess(std::move(c)); // call with rvalue
}

auto print = [](const auto& str) {
	std::cout << str << std::endl;
};

class Clazz {
public:
	Clazz() {
		print("constructor");
	}
	Clazz(const Clazz& other) {
		// Classical copy construction for lvalues
		print("copy constructor");
	}
	Clazz(Clazz&& other) noexcept {
		print("move constructor");
		// Move constructor for rvalues: moves content from 'other' to this
	}
	Clazz& operator=(const Clazz& other) {
		// Classical copy assignment for lvalues
		print("assignment");
		return *this;
	}
	Clazz& operator=(Clazz&& other) noexcept {
		// Move assignment for rvalues: moves content from 'other' to this
		print("move assignment");
		return *this;
	}
	// ...
};
void TestMove() {
	Clazz anObject;
	Clazz anotherObject1(anObject); // Calls copy constructor
	Clazz anotherObject2(std::move(anObject)); // Calls move constructor
	anObject = anotherObject1; // Calls copy assignment operator
	anotherObject2 = std::move(anObject); // Calls move assignment operator
}

template<typename T>
class MemoryBlock
{
public:
	explicit MemoryBlock(size_t length)
		: _length(length)
		, _data(new T[length]){
	}

	~MemoryBlock(){
		if (_data != nullptr)
		{
			delete[] _data;
		}
	}

	MemoryBlock(const MemoryBlock& other)
		: _length(other._length)
		, _data(new T[other._length])
	{
		std::copy(other._data, other._data + _length, _data);
	}

	MemoryBlock& operator=(const MemoryBlock& other)
	{
		if (this != &other)
		{
			delete[] _data;
			_length = other._length;
			_data = new int[_length];
			std::copy(other._data, other._data + _length, _data);
		}
		return *this;
	}

	/// <summary>
	/// constructor takes an rvalue reference to the class type
	/// Assign all the data members from the rvalue reference to the current object
	/// Assign the data members from the rvalue reference to default values
	/// </summary>
	
	MemoryBlock(MemoryBlock&& other)
		: _data(nullptr)
		, _length(0)
	{
		_data = other._data;
		_length = other._length;
		other._data = nullptr;
		other._length = 0;
	}

	// alternative way
	MemoryBlock(MemoryBlock&& other) 
		: _data(nullptr)
		, _length(0)
	{
		*this = std::move(other);
	}

	/// <summary>
	/// move assignment operator that takes an rvalue reference to the class type and returns a reference to it
	/// 
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

	// Retrieves the length of the data resource.  
	size_t Length() const
	{
		return _length;
	}

private:
	size_t _length; // The length of the resource.  
	T* _data; // The resource.  
};

void testMoveMemoryBlock()
{
	// Create a vector object and add a few elements to it.  
	std::vector<MemoryBlock<int>> v;
	v.push_back(MemoryBlock<int>(25));
	v.push_back(MemoryBlock<int>(75));

	// Insert a new element into the second position of the vector.  
	v.insert(v.begin() + 1, MemoryBlock<int>(50));
}
/*
Output ....

In MemoryBlock(size_t). length = 25.
In MemoryBlock(MemoryBlock&&). length = 25. Moving resource.
In ~MemoryBlock(). length = 0.
In MemoryBlock(size_t). length = 75.
In MemoryBlock(MemoryBlock&&). length = 25. Moving resource.
In ~MemoryBlock(). length = 0.
In MemoryBlock(MemoryBlock&&). length = 75. Moving resource.
In ~MemoryBlock(). length = 0.
In MemoryBlock(size_t). length = 50.
In MemoryBlock(MemoryBlock&&). length = 50. Moving resource.
In MemoryBlock(MemoryBlock&&). length = 50. Moving resource.
In operator=(MemoryBlock&&). length = 75.
In operator=(MemoryBlock&&). length = 50.
In ~MemoryBlock(). length = 0.
In ~MemoryBlock(). length = 0.
In ~MemoryBlock(). length = 25. Deleting resource.
In ~MemoryBlock(). length = 50. Deleting resource.
In ~MemoryBlock(). length = 75. Deleting resource.

*/
