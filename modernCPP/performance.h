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
///				-- memory allocation a system call ?
///					-- Conceptually, a function for allocating memory (new /malloc) searches a collection of free memory blocks
///					-- If no free memory blocks are available to fill the request, the allocation function makes an expensive call to OS kernel 
///						for an additional large memory block from the system’s pool of available memory.
///						The memory returned by the kernel may or may not be cached in physical RAM, perhaps resulting in even more delay 
///						-- so If there are space available in the committed pages, memory manager will allocate the requested space without changing the kernel mode. 
///						-- On Windows, the lower mechanism is VirtualAlloc(). on LInux mmap()/sbrk() 
///						-- Subsequent allocations will use smaller parts of those large pages without incurring a system call.
///             -- Is the heap shared by different processes and managed by the OS. What about private heap?
///						-- The heap is not shared between processes. It's shared between threads though.
///						-- Any changes to the free block collection must be thread-safe. If several threads make frequent calls to allocate or free memory, 
///							they experience contention for the memory manager as a resource, causing all but one thread to wait.
/// 
///  			-- operators new and delete or with the functions malloc and free and are costly
///				-- The heap can easily become fragmented when objects of different sizes are allocated and deallocated in random order.
///				-- The heap manager can spend a lot of time cleaning up spaces that are no longer used and searching for vacant spaces
///				-- Objects that are allocated in sequence are not necessarily stored sequentially in memory. 
///					They may be scattered around at different places when the heap has become fragmented. This makes data caching inefficient		
/// </summary>
/// 
/// This structure or class should be aligned by at least the cache line size in order to avoid multiple threads writing to the same cache line. 
/// The cache line size is typically 64 bytes on contemporary processors.
/// 


/// <summary>
/// optimization
///		1. Make use of good compilers and use Your Compiler with right flags for optimization
///		2. Use Better Algorithms - especially for searching and sorting
///		3. Use Better Libraries - standard C++ template and runtime libraries are sometime generic and tuned for efficiency
///						-- Optmize datastructures - google dense map, facebook folly, 
///						-- better concurrency, lockfree - boost, intel tbb, 
///						-- optmize memory management - object pools, avoid expensive copying, 
///		4. Reduce Memory Allocation and Copying
///		5. Remove Computation
///		6. Measure performance (80/20 rule - a program spends 80% of its run time in 20 % of its code.)
///			-- Profile Program Execution
///		7. Precomputation - earlier in the program, at link time, compile time, or design time.
///		8. Caching - Reduce computation by saving and reusing the results of an expensive computation rather than recomputing them
///		9. Hashing - Compute a compact numerical summary(the hash) of a larger data structure such as a variable - length character string.
///		10. Copy-on-write -Instead of copying a dynamic member variable when an object is copied, the two 
///			instances share a single copy of the dynamic variable.Copying is deferred until either instance wants to modify the variable.
///		11. Double-Checking
///			 -- The cache is checked quickly to see if the desired value is there, and if not the value is fetched or computed by a more expensive process.
///			 -- Comparing two std::string instances for equality normally requires comparing them character - by - character.
///					-- However, a preliminary comparison of the lengths of the two strings can quickly rule out equality.
///					-- The hashes of two inputs can be compared efficiently for equality;  if the hashes are different, the inputs are not equal.
/// 
/// 
///  Contexts Swtich :
/// -------------------------
///		1. Context switch from one thread to another in same program
///			--saving the processor’s registers  for the thread being suspended
///			-- loading the saved registers for the thread being resumed
///			-- resumed thread data may not be in cache, so there is an initial period of slow execution while the new context is loaded into cache
///     2. Context switch from one program to another program
///			--- All dirty cache pages (ones with written data that has not reached main memory) must be flushed to physical memory.
///			--- All the processor registers are saved.
///			--- Then the physical-to-virtual memory page registers in the memory manager are saved.Next
///			---  the physical - to - virtual memory page registers for the new process are reloaded
///			---  and the processor registers for the new process are reloaded.
///			---  Finally, execution resume, but the cache is empty, so there is an initial period of slow performance 
///						and heavy memory contention while the cache is refilled.
///	 Memory Access :
///			1. Multicore processor and their associated cache memories act more or less independently 
///				of one another to achieve better performance.However, all execution units share the same main memory.
///			2. When an execution unit writes a value, the value goes first into cache memory. It eventually has 
///				to be written through the cache all the way to main memory, so that the value is visible to other execution units.
/// </summary>


// optimize following function

std::string remove_ctrl(std::string s) {
	std::string result;
	for (int i = 0; i<s.length(); ++i) {
		if (s[i] >= 0x20)
			result = result + s[i];
	}
	return result;
}

// 1. get the string by const reference, or provide rvalue reference
// 2. get the return by reference
void remove_ctrl_str(const std::string& s, std::string& result) {
	result.clear();
	// 3. reserve it in the begining, 17% improvement
	result.reserve(s.length());

	for (const auto& it : s) {
		//4.  String iterators are simple pointers into the character buffer.
		//   That saves two dereference operations versus the non - iterator code in the loop.
		if (it >= 0x20) {
			// 5. remove the temporary .. 13x improvements
			result += it;
		}
	}
}

// 6. Use Character Arrays Instead of Strings
// 6 times faster than predecessor
void remove_ctrl_cstr(const char* src, char* dest, const size_t size) {
	for (size_t i = 0; i < size; ++i) {
		if (src[i] >= 0x20) {
			*dest++ = src[i];
		}
	}
}


/// <summary>
/// --- Excellent cache locality may, however, contribute to a simple performance measurement
///			 being misleading.In general, other operations between calls to remove_ctrl_cstrings() 
///			flush the cache.But when it is called in a tight loop,instructions and data stay in cache.
/// </summary>


void TestPerformance()
{
	
}

