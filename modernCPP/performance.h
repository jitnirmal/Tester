#pragma once

#include <iostream>
using namespace std;
#include <map>

/// <summary>
/// 1. Use the noexcept for the functions you are sure will never throw exceptions.
///		-- helps move operations to be used by stl containers
///		-- compiler optimizations
/// 2.  Avoid the repeated execution of try/catch block inside bottlenecks/critical path.
/// 3.  If you have to use C++ streams, use "\n" instead of std::endl since std::endl also flushes the stream.
/// 4.  If the incremented object is a primitive type, there is no difference between prefix and postfix operators. 
///			However, if it is a composite object, the postfix operator causes the creation of a temporary object, while the prefix operator does not.
/// 5. Use the assignment composite operators (like in a += b) instead of simple operators combined with assignment operators (like in a = a + b).
/// /// </summary>




/// <summary>
/// Stack (FIFO) :  all variables and objects should preferably be declared inside the function in which they are used.
///					It is used for storing function return addresses (i.e. where the function was called from), 
///					function parameters, local variables, and for saving registers that have to be restored before the function returns.
///					most efficient memory space to store data because the same range of memory addresses is reused again and again. 
///					For smaller data/arrays, it is almost certain that this part of the memory is mirrored in the level-1 data cache, where it is accessed quite fast.
///					all variables and objects should preferably be declared inside the function in which they are used.
/// Global or static storage : variables that can be accessed from any function
///					usually divided into three parts
///						-- one for constants that are never modified by the program
///						-- one for initialized variables that may be modified by the program
///						-- one for uninitialized variables that may be modified by the program
///					The advantage of static data is that it can be initialized to desired values before the program starts. 
///					The disadvantage is that the memory space is occupied throughout the whole program execution,
/// Volatile : The volatile keyword specifies that a variable can be changed by another thread. 
///				-- This prevents the compiler from making optimizations that rely on the assumption that the variable always has the value 
///				it was assigned previously in the code
///				-- volatile doesn't mean atomic. It doesn't prevent two threads from attempting to write the variable at the same time.
///	Dynamic memory allocation
///				-- operators new and delete or with the functions malloc and free and are costly
///				-- The heap can easily become fragmented when objects of different sizes are allocated and deallocated in random order.
///				-- The heap manager can spend a lot of time cleaning up spaces that are no longer used and searching for vacant spaces
///				-- Objects that are allocated in sequence are not necessarily stored sequentially in memory. 
///					They may be scattered around at different places when the heap has become fragmented. This makes data caching inefficient		
/// </summary>
/// 
/// This structure or class should be aligned by at least the cache line size in order to avoid multiple threads writing to the same cache line. 
/// The cache line size is typically 64 bytes on contemporary processors.
/// 
void TestPerformance()
{
	
}

