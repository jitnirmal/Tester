#pragma once  
#include <utility> // std::move<T>
#include <iostream>  
#include <algorithm>  
#include <vector> 
#include <deque>
/// -------------------------------------------------------------------------------------------------------------------------------------
///       FAQ-1          STD::MOVE 
/// -------------------------------------------------------------------------------------------------------------------------------------
/// 1. Move semantics are a key feature that drives the performance improvements of modern C++. 
///		-- avoid redundant deep-cloning operations with high performance costs
/// 2. They enable moving, rather than copying, resources or , especially, objects which are expensive to copy.
///		-- When moving an object, the destination object steals the resource straight from the source object, and the source object is reset
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
/// 13. Do not forget to mark your move-constructors and move-assignment operators as noexcept (unless they might throw an exception, of course). 
///		Not marking them noexcept prevents STL containers and algorithms from utilizing them and resorts to a regular copy/assignment under certain conditions.
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
/// <summary>
/// If the expression initializing a universal reference is an lvalue, the universal reference becomes an lvalue reference.
/// If the expression initializing the universal reference is an rvalue, the universal reference becomes an rvalue reference.
/// If you can take the address of an expression, the expression is an lvalue
/// 
/// Widget&& var1 = someWidget; 
/// You can take the address of var1, so var1 is an lvalue. 
/// auto&& var2 = var1;
/// var2’s type declaration of auto&& makes it a universal reference, and because it’s being initialized with var1 (an lvalue), var2 becomes an lvalue reference. 
/// 
///  It’s as if var2 were declared like this:
///  Widget& var2 = var1;
/// 
/// example 2 ::
/// std::vector<int> v;
/// auto&& val = v[0];               // val becomes an lvalue reference (see below)
/// val is a universal reference, and it’s being initialized with v[0], i.e., with the result of a call to std::vector<int>::operator[]. 
/// 
/// template<typename T>
/// void f(T&& param);               // “&&” might mean rvalue reference
/// f(10);                           // 10 is an rvalue
/// 
/// int x = 10;
/// f(x);                            // x is an lvalue
/// 
/// template<typename T>
/// void f(std::vector<T>&& param);     // “&&” means rvalue reference
/// 
/// template<typename T>
/// void f(T&& param);               // deduced parameter type ⇒ type deduction;
///									 // && ≡ universal reference
/// 
/// template<typename T>
/// class Widget {
/// 		Widget(Widget&& rhs);        // fully specified parameter type ⇒ no type deduction;
///      };                // && ≡ rvalue reference
/// 
/// template<typename T1>
/// class Gadget {
/// 	template<typename T2>
/// Gadget(T2&& rhs);            // deduced parameter type ⇒ type deduction;
///	};					&& ≡ universal reference	
/// 
/// void f(Widget&& param);          // fully specified parameter type ⇒ no type deduction;
/// 							 // && ≡ rvalue reference
/// 
/// Even the simple addition of a const qualifier is enough to disable the interpretation of “&&” as a universal reference:
/// template<typename T>
/// void f(const T&& param);               // “&&” means rvalue referencetemplate<typename T>
/// 
/// 
/// Widget makeWidget();                       // factory function for Widget
/// Widget&& var1 = makeWidget()               // var1 is an lvalue, but
///											   its type is rvalue reference (to Widget)
/// 
/// Widget var2 = static_cast<Widget&&>(var1); // the cast expression yields an rvalue, but
///													its type is rvalue reference  (to Widget)
/// 
/// /// </summary>


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

void TestMove2() {
	Clazz Object1;

	// just rvalue reference.. no constructor call for all 3 following cases
	Clazz&& Object2 = std::move(Object1);
	Clazz&& Object3 = static_cast<Clazz&&>(Object1);
	auto&& Object4 = Object1; // Clazz&
	auto&& Object5 = Clazz(); // Clazz&&
	auto&& Object6 = std::move(Object1); // Clazz&&

										 // move constructor
	Clazz Object7 = std::move(Object4);


	// const + move constructor
	Clazz Object8 = Clazz();

	int var1 = 10;
	auto&& var2 = var1;
}


void overloaded(int const &arg) { std::cout << "by lvalue\n"; }
void overloaded(int && arg) { std::cout << "by rvalue\n"; }

template< typename t >
/* "t &&" with "t" being template param is special, and  adjusts "t" to be
(for example) "int &" or non-ref "int" so std::forward knows what to do. */
void forwarding(t && arg) {
	std::cout << "via std::forward: ";
	overloaded(std::forward< t >(arg));
	std::cout << "via std::move: ";
	overloaded(std::move(arg)); // conceptually this would invalidate arg
	std::cout << "by simple passing: ";
	overloaded(arg);
}

int testForward() {
	std::cout << "initial caller passes rvalue:\n";
	forwarding(5);
	std::cout << "initial caller passes lvalue:\n";
	int x = 5;
	forwarding(x);
	return 0;
}

/// <summary>
/// test with queue
/// </summary>


template<typename T>
struct Queue
{
	void Enqueue(const T& value)
	{
		// this will never use move constructor as l value reference
		// removing this, lvalue will not compile
		_q.push_front(std::move(value));
	}
	void Enqueue(T&& value)
	{
		// this will use move constructor for temporaries, or can cast lvalue to rvalue
		_q.push_front(std::move(value));
	}
	void Dequeue(T& value)
	{
		value = std::move(_q.front());
		_q.pop_front();
	}
	std::deque<T> _q;
};

struct A {
	A(int x) :val(x) { puts("const"); }
	A(const A&) { puts("copy const"); }
	A(A&&) { puts("move const"); }
	A& operator=(const A&) { puts("assign"); return *this; }
	A& operator=(A&&) { puts("move assign"); return *this; }
	~A() { puts("dest"); }


	int val;
};

void testMove()
{
	Queue<A> Q;
	A a(1);
	Q.Enqueue(a);
	Q.Enqueue(A(2));

	A result(0);

	Q.Dequeue(result);
	result.val = 10;
	std::cout << result.val << std::endl;
}


/// <summary>
/// memory block
/// </summary>
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
