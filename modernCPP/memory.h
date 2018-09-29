#pragma once

#include <iostream>

#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>

/// <summary>
/// 1. Memory leaks 
///		-- Use RAII, prefer make_unique or make_shared, For multiple objects, prefer using standard containers like vector and unordered_map 
/// 2. Advantage of nullptr
///		-- nullptr = NULL - 0 which keeps confusion “maybe an integer value and maybe a pointer” value, so use nullptr
/// 3. MIxing new/malloc/free/delete
///    --- The C++ operators new and delete invoke constructors or destructors,The C-style functions malloc(), calloc(), free(), and realloc() don’t
///    ---  there is no guarantee that the mechanism used by new and delete to acquire and release raw memory is compatible with malloc() and free()
/// 4. New vs malloc
///    --- malloc() takes a number of bytes as its argument; it returns a void* pointing to unitialized storage
///			void* p1 = malloc(40);
///    ---  new is an operator that takes a type and its arguments; it returns a pointer to initialized object of its type
///			Circle* pc1 = new Circle(Point(0,0),10)
///    --- new can be overloaded
///    --- new throws bad_alloc
/// 5. No Memory leak if constructor throws exception
///		internally try { new(tmp) Fred();  p = (Fred*)tmp; }   // The pointer is assigned only if the ctor succeeds
///				  catch (...) { 	operator delete(tmp);  	throw;}                 // Re-throw the exception
/// 
/// 6. allocate / unallocate an array of things
///		Fred* p = new Fred[100];
//       delete[] p;
/// 7. Auto Ptr Disadvatage
///	   --- The main drawback of std::auto_ptr is that it has the transfer-of-ownership semantic. 
///        That makes it impossible to store std::auto_ptr in STL containers because the containers use the copy constructor 
///         when you store or get an element.
///				  class X{};  std::vector<std::auto_ptr<X> > vecX;  vecX.push_back(new X); 
///			     std::auto_ptr<X> pX = vecX[0];  // vecX[0] is assigned NULL
///			Unique_ptr can be used with vectors due to disabled copy and move semantics
/// 
///    --- cannot use them with pointer to array  auto_ptr<T> p2( new T[n] );
///        use vector instead or std::unique_ptr<int[]> p(new int[10]); or std array
/// 8. Why doesn’t delete null out its operand
///		reason is that the operand of delete need not be an lvalue. Consider:
///		delete p+1; delete f(x);
/// </summary>


void testAutoPtr() {
	struct X {};  
	std::vector<std::auto_ptr<X>> vecAX;  
	vecAX.push_back(std::auto_ptr<X>(new X));
	vecAX.push_back(std::auto_ptr<X>(new X));
	vecAX.push_back(std::auto_ptr<X>(new X));
	auto pAX = vecAX[0];   //vecX[0] is assigned NULL

	std::vector<std::unique_ptr<X>> vecUX;
	vecUX.push_back(std::unique_ptr<X>(new X));
	vecUX.push_back(std::unique_ptr<X>(new X));
	vecUX.push_back(std::unique_ptr<X>(new X));
//	auto pUX = vecUX[0];   //this is compiler error
}

/// <summary>
/// Constructors 
/// 1. Is the default constructor for Fred always Fred::Fred()
///		No. A “default constructor” is a constructor that can be called with no arguments.
///		Fred(int i=3, int j=5);   // Default constructor: can be called with no args
/// 2. Which constructor gets called when I create an array of Fred objects? 
///		Fred’s default constructor, If your class doesn’t have a default constructor, you’ll get a compile-time error 
/// 3. Constructor initialization list saves temporaries to be created
///		--Fred::Fred() { x_ = whatever; } temporary object to be created, assigned and destructed, which is inefficient.
///		-- non-static const and non-static reference data members must need to be initialized in initialization list
/// 4. How should initializers be ordered in a constructor’s initialization list
///		--- Immediate base classes (left to right), then member objects (top to bottom).
///     --- Member variables are always initialized in the order they are declared in the class definition; 
///				the order in which you write them in the constructor initialization list is ignored.Make sure the constructor code doesn't 
///				confusingly specify a different order.
/// 5. Named Constructor Idiom
///		--- A technique that provides more intuitive and/or safer construction operations for users of your class.
/// 6. you can’t I initialize my static member data in my constructor’s initialization list
///     --- you must explicitly define your class’s static data members.
///     ---  static data members must be explicitly defined in exactly one compilation unit
/// 7. purpose of the explicit keyword
///		--- optional decoration for constructors and conversion operators to avoid implicitly cast for an expression to its class type.
///		Foo(int x); --> Foo a = 42;
/// 8. Avoid calling virtual functions in constructors and destructors.
///			--- Virtual functions only "virtually" always behave virtually: Inside constructors and destructors, they don't.
/// 9. Make base class destructors public and virtual, or protected and nonvirtual.
///			--- If destruction through a pointer to a base Base should be allowed, then Base's destructor must be public and virtual
/// 10. If a destructor called during stack unwinding exits with an exception, terminate is called.So destructors should generally 
///			catch exceptions and not let them propagate out of the destructor.
/// </summary>


class Fred {
public:
	Fred() : i_(10)  // Okay: you can (and should) initialize member data this way
	//	, j_(42)  // Error: you cannot initialize static member data like this
	{}
	// ...
private:
	int i_;
	static int j_;
};
int Fred::j_ = 42;


void TestNamedConstructor()
{
	class Point {
	public:
		static Point rectangular(float x, float y) { return Point(x, y); }      // Rectangular coord's
		static Point polar(float radius, float angle) { return Point(radius*std::cos(angle), radius*std::sin(angle)); }  // Polar coordinates
	private:
		Point(float x, float y) : x_(x), y_(y) { }
			float x_, y_;
	};


	Point p1 = Point::rectangular(5.7, 1.2);   // Obviously rectangular
	Point p2 = Point::polar(5.7, 1.2);         // Obviously polar


	
}

void TestMemory()
{
	testAutoPtr();
}