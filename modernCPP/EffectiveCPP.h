#pragma once
#include <iostream>
#include <vector>

/// <summary>
/// Perfornace Vtune
///		1. Branch mispridctions
///		2. Cache misses, false sharing
///		3. CPU core scheduling
///		4. lock and datastructure timings
///		5. function timings/system calls
/// </summary>

/// <summary>
/// 1. Have assignment operators return a reference to *this.
///		--- so you can chain them together x = y = z = 15;
/// 2. Never call virtual functions during construction or destruction.
///		-- virtual functions resolve to the base class
///		-- RTTI	dynamic_cast and typeid treat the object as a base class type
/// 3. Prevent exceptions from leaving destructors
///		-- during destructor calls, a second Widget destructor throws an exception.
///			these are two simultaneously active exceptions, and that’s one too many for C++.
/// 4. Declare destructors virtual in polymorphic base classes.
/// 5. Handle assignment to self in operator=
///		-- the object which should not have been changed by the assignment to self 
///			may find itself holding a pointer to a deleted object (self delete)
///		-- a careful ordering of statements can yield exception - safe code not to delete
///			pb until after we’ve copied what it points to
///			Widget& Widget::operator=(const Widget& rhs) { auto pOrig = pb;  pb = new Data(*rhs.pb); delete pOrig; return *this;}
///		-- implement assignment as part of copy constructor		
///			Widget& Widget::operator=(const Widget& rhs){
///				Widget temp(rhs); // make a copy of rhs’s data
///				swap(temp); // swap *this’s data with the copy’s
///				return *this;}
/// 6. Branch your code with if/else with care
///		-- branch in flow , can decrease effectiveness of instruction prefetching, caching, and pipelining, and hence impact performance
/// 7. inline code bloat can lead to additional paging, a reduced instruction cache hit rate, 
///			and the performance penalties that accompany these things.
/// 7. Prefer pass-by-reference-to-const to pass-byvalue.It’s typically more efficient and it avoids the slicing problem.
/// 8. Never return a pointer or reference to a local stack object, a reference to a heap - allocated object,
/// 9. Avoid casts whenever practical, especially dynamic_casts in performance-sensitive code.
/// 10. Template metaprogramming can shift work from runtime to compile- time, thus enabling 
///		earlier error detection and higher runtime performance.

/// Templates
///		1. TMP can be used to generate custom code based on combinations of policy choices, 
///		and it can also be used to avoid generating code inappropriate for particular types.

/// <summary>
/// Distinguish between prefix and postfix forms of increment and decrement operators.
///		UPInt& operator++(); // prefix --
///		const UPInt operator++(int); // postfix -, this is generally less efficient due to temporary object
/// </summary>


///  INLINING
/// 1. Limit most inlining to small, frequently called functions. This facilitates debugging and binary upgradability,
///		 minimizes potential code bloat, and maximizes the chances of greater program speed
/// 2. virtual function call cannot be inlined
/// 3. Use the non-virtual interface idiom (NVI idiom), a form of the 
///		Template Method design pattern that wraps public non - virtual
///		member functions around less accessible virtual functions.
/// </summary>

/// <summary> Memory
/// 1. To prevent resource leaks, use RAII objects that acquire resources in their constructors and release them in their destructors
/// 2. Common RAII class copying behaviors are disallowing copying and performing reference counting, but other behaviors are possible.
/// 3. If you use [] in a new expression, you must use [] in the corresponding delete expression.
/// </summary>


void TestExceptionalCPP()
{
}




