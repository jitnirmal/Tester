#pragma once
#include <iostream>
#include <vector>

/// <summary>
/// 1. A vtbl is usually an array of pointers to functions (Some compilers use a form of linked list)
/// 2. Each class in a program that declares or inherits virtual functions has its own vtbl, 
///			and the entries in a class’s vtbl are pointers to the implementations of the virtual functions for that class
///		--  There should be only one virtual table per class 
/// 3. vtbl for class C1 above would be placed in the object file containing the definition of C1::~C1, 
///			and the vtbl for class C2 would be placed in the object file containing the definition of C2::~C2
/// 4. Each object whose class declares virtual functions carries with it a hidden vptr that points to the virtual table for that class.
///	5. INLINE : Virtual functions can be inlined when invoked through objects, but most virtual function 
///			calls are made through pointers or references to objects, and such calls are not inlined.
///			as “virtual” means “wait until runtime to see which function is called
/// /// COST
///		a. space for a virtual table for each class that contains virtual functions.
///		b. The size of a class’s vtbl is proportional to the number of virtual functions declared for that class
///		c. the code generated for the statement 
///			pC1->f1();
///			(*pC1->vptr[i])(pC1); // i is index for f1
///			This is almost as efficient as a non-virtual function call: on most machines it executes only a few more instructions.
///				The cost of calling a virtual function is thus basically the same as that of calling a function through a function pointer.
///			Virtual functions per se are not usually a performance bottleneck.
///		d. With multiple inheritance, offset calculations to find vptrs within objects become more complicated; 
///			there are multiple vptrs within a single object(one per base class); and special vtbls must be generated
///			As a result, both the per - class and the per - object space overhead for virtual functions increases, 
///			and the runtime invocation cost grows slightly, too.
///		e.  RTTI lets us discover information about objects and classes at runtime, That information is stored in an object of type type_info,
///			and you can access the type_info object for a class by using the typeid operator.
///			-- There only needs to be a single copy of the RTTI information for each class, only if that type has at least one virtual function
///			-- the space cost of RTTI is an additional entry in each class vtbl plus the cost of the storage for the type_info object for each class.
///				--This penalty does not have a fixed cost. It is dependent on the complexity of the function and the frequency with which it is invoked.
///			-- When you throw in multiple inheritance and/or virtual inheritance, object creation involves an additional cost. 
///				This additional cost comes from having to set multiple vptrs and added indirection of virtual function invocation.
/// 
/// 
/// Virtual functions seem to inflict a performance cost in several ways:
///		1. The vptr must be initialized in the constructor.
///		2. A virtual function is invoked via pointer indirection.We must fetch the pointer to the function table and then access the correct function offset.
///		3. Inlining is a compile - time decision.The compiler cannot inline virtual functions whose resolution takes place at run - time.
///			--Evaluating the performance penalty of a virtual function is equivalent to evaluating the penalty resulting from failure to inline that same function. 
/// </summary>

/// C1’s vtabl 
///     C1’s type_info object
///		implementation of C1::f1
///		implementation of C1::f2
///		implementation of C1::f3
///		implementation of C1::~C1
class C1 {
public:
	C1();
	virtual ~C1();
	virtual void f1();
	virtual int f2(char c) const;
	virtual void f3(const std::string& s);
	void f4() const;
};

/// <summary>
/// C2’s vtabl 
///		implementation of C2::f1
///		implementation of C1::f2
///		implementation of C1::f3
///		implementation of C2::~C2
///		implementation of C2::f5

/// </summary>
class C2 : public C1 {
public:
	C2(); // nonvirtual function
	virtual ~C2(); // redefined function
	virtual void f1() override; // redefined function
	virtual void f5(char *str); // new virtual function
};

/// <summary>
/// the dreaded multiple inheritance diamond
/// </summary>
class A {  };
class B : virtual public A {  };
class C : virtual public A {  };
class D : public B, public C {  };


/// <summary>
/// Requiring Heap-Based Objects: prohibit making on stack
///		-- make the destructor private and the constructors public
///		-- you can introduce a privileged pseudo-destructor function that has access to the real destructor.
/// </summary>

class UPNumber {
public:
	UPNumber();
	// pseudo-destructor (a const member function, because even const objects may be destroyed)
	void destroy() const { delete this; }
private:
	~UPNumber();
};

void TestStackRestrictedObjects() {
	//UPNumber n; //error
	UPNumber *p = new UPNumber;
	//delete p;  //error
	p->destroy(); //fine
}

void TestVTable()
{
}

