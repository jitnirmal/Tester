#pragma once
#include <iostream>
using namespace std;
/// ----------------------------------------------------------------------------------------------
///								STATIC
/// ----------------------------------------------------------------------------------------------
///  Static when applied to a variable declared outside of a block, it defines a global variable with internal linkage
///  A static variable inside block , will  retains its value even after the scope in which it has been created has been exited
/// 
/// Static member variables
///		-- Static members are not associated with class objects
///		class Something { static int s_value; };
///		int Something::s_value=12;


/// ----------------------------------------------------------------------------------------------
///								VIRTUAL
/// ----------------------------------------------------------------------------------------------
/// 
/// 
///		


/// ----------------------------------------------------------------------------------------------
///								Memory Management
/// ----------------------------------------------------------------------------------------------
/// 
///  1. Const Data : stores string literals and other data whose values are known at compile time.
///	 -- All data in this area is available during the entire lifetime of the program.
///	 -- Further, all of this data is read - only, and the results of trying to modify it are undefined.
/// 
///  2. Stack : stores automatic variables. Typically allocation is much faster than for dynamic storage(heap or free store) 
///			because a memory allocation involves only pointer increment rather than more complex management.
/// 
///  3. Free Store : The free store is one of the two dynamic memory areas, allocated / freed by new / delete.
///		Objectlifetime can be less than the time the storage is allocated
/// 
///  4. Heap : The heap is the other dynamic memory area allocated / freed by malloc / free and their variants.
///			Note that while the default global new and delete might be implemented in terms of 	malloc and free by a particular compiler, 
///			the heap is not the same as free store and memory allocated in one area cannot be safely deallocated in the other.
///	5.  Global / Static   Global or static variables and objects have their storage allocated at program startup, but
///			may not be initialized until after the program has begun executing. 
///			For instance, a static variable in a function is initialized only the first time program execution passes through its
///			definition.The order of initialization of global variables across translation units is not defined, 
///			and special care is needed to manage dependencies between global objects(including class statics).

class Base
{
public:
	virtual void fun(int x = 200){
		cout << "Base::fun(), x = " << x << endl;
	}
};

class Derived : public Base
{
public:
	virtual void fun(int x = 100) {
		cout << "Derived::fun(), x = " << x << endl;
	}
};


