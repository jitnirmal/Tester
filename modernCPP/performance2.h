#pragma once

#include <iostream>
using namespace std;
#include <map>

/// <summary>
/// 1. empty destructors
///		writing an empty destructor prevents the compiler from implementing certain optimizations.
///		--copying an array of a trivial class with an empty destructor yields the same, non-optimized, assembler code as copying with a handcrafted for loop
///		-- However, if we remove or declare the destructor default, the compiler optimize std::copy to utilize memmove instead of a loop
/// 
/// 
/// 2. Performance testing is usually too late in the development process
///  -- recommendation is to measure early and detect regression as soon as possible by adding performance tests to your nightly builds, and so on.
///  -- It's also important to test your application with realistic test data early on (orders per second, data size (rules, price, position))
///	 -- Plotting your data is a very effective way of understanding the data you have collected
///			-- Once you plot your data, you are going to see the outliers and patterns that are usually hard to find in a table full of numbers.
/// 
/// Profilers : There are two main categories of profilers: 
///		a) sampling profilers :
///			--Sampling profilers create a profile by looking at the running program's state at even intervals—typically, every 10 ms
///			-- Sampling profilers usually have a minimum impact on the program's actual performance
///			--  it's also possible to build the program in release mode with all optimizations turned on.
///			Drawback :
///			--A drawback of sampling profilers is their inaccuracy and statistical approach,		
///		b) instrumentation profilers :  inserting code into the program to be analyzed in order to gather information about how frequently each function is being executed
///			-- the inserted instrumentation code records each entry and exit point.
///		c) a hybrid of sampling and instrumentation.  example gprof 
/// 
/// Steady vs. System Time
///		a) The steady clock is best for measuring time intervals
///			-- Class std::chrono::steady_clock represents a monotonic clock. The time points of this clock cannot decrease as physical time moves forward.
///				 This clock is not related to wall clock time, and is best suitable for measuring intervals.
///		b) As opposed to the system_clock, which is not monotonic (i.e. the time can decrease if, say, the user changes the time on the host machine.)
/// 
/// Commands - sysctl -a hw
///		hw.memsize: 17179869184 
///		hw.cachelinesize: 64
///		hw.l1icachesize : 32768 (32KB)/(0.5 ns)
///		hw.l1dcachesize : 32768 (32KB)
///		hw.l2cachesize : 262144 (2MB) / (7 ns)
///		hw.l3cachesize : 6291456 (6 MB)
///		main memory		:			()/(100ns)
///  When accessing a byte in memory, the machine is not only fetching the byte we asked for; instead, the machine always fetches a cache line,
///		 which in this case is 64 bytes. The various caches between the CPU and main memory keep track of 64 byte blocks instead of individual bytes.
///	 Temporal locality :  Accessing data that has recently been used and, therefore, potentially already resides in the cache will make your program faster.
///  spatial locality  :  Accessing data that is located near some other data you are using will increase the likelihood that the data you need is already 
///						in a cache line fetched from main memory earlier
/// </summary>


void testCacheLocality(){
	constexpr auto kL1CacheCapacity = 32768; // The L1 Data cache size 
	constexpr auto kSize = kL1CacheCapacity / sizeof(int);
	using MatrixType = std::array<std::array<int, kSize>, kSize>;

	auto cache_thrashing = [](MatrixType& matrix) 
	{
		auto counter = 0;
		for (auto i = 0; i < kSize; ++i) {
			for (auto j = 0; j < kSize; ++j) {
				//matrix[i][j] = counter++;
			}
		}
	};
}

void TestPerformance2()
{
	
}


/// <summary>
/// how to get symbol info for release build
/// step 1 : make release and debug build
/// step 2 : strip the debug info file and keep it with release build
/// step 3 : link the debug info file with binary when need debug info...
/// 
/// g++ -Wall -fexceptions -g -o main.cpp tester
/// objcopy --only - keep - debug foo tester.dbg to create a file containing the debugging info.
/// objcopy --strip - debug foo to create a stripped executable.
/// objcopy --add-gnu-debuglink = tester.dbg tester to add a link to the debugging info into the stripped executable.
/// 
/// 
/// ------------------------------------------------------------------------------------------------------------------------------------------
/// /// objcopy : utility copies the contents of an object file to another. objcopy uses the GNU BFD Library to read and write the object files.
/// It can write the destination object file in a format different from that of the source object file. 
///  Note that objcopy should be able to copy a fully linked file between any two formats. 
/// ------------------------------------------------------------------------------------------------------------------------------------------
/// nm : GNU nm lists the symbols from object files objfile
/// For each symbol, nm shows:
///  -- The symbol value
///  -- The symbol type
/// A   : The symbol’s value is absolute, and will not be changed by further linking.
/// B/b : The symbol is in the uninitialized data section(known as BSS).
/// D/d : The symbol is in the initialized data section.
/// G/g : The symbol is in an initialized data section for small objects
/// 
/// 0000000000202018 B __bss_start
/// 0000000000202130 b completed.7696
/// U __cxa_atexit@@GLIBC_2.2.5
/// w __cxa_finalize@@GLIBC_2.2.5
/// 0000000000202000 D __data_start
/// 0000000000202000 W data_start

/// ------------------------------------------------------------------------------------------------------------------------------------------
/// ldd - print shared object dependencies
/// 
/// ldd testerd
/// linux - vdso.so.1 (0x00007fffc6bb8000)
/// libstdc++.so.6 = > / usr / lib / x86_64 - linux - gnu / libstdc++.so.6 (0x00007f377a627000)
/// libgcc_s.so.1 = > / lib / x86_64 - linux - gnu / libgcc_s.so.1 (0x00007f377a40f000)
/// libc.so.6 = > / lib / x86_64 - linux - gnu / libc.so.6 (0x00007f377a01e000)
/// libm.so.6 = > / lib / x86_64 - linux - gnu / libm.so.6 (0x00007f3779c80000)
/// lib64 / ld - linux - x86 - 64.so.2 (0x00007f377abb3000)
/// ------------------------------------------------------------------------------------------------------------------------------------------		
/// objdump - display information from object files.
/// ------------------------------------------------------------------------------------------------------------------------------------------		
/// ulimit -c unlimited
/// http://www.muppetlabs.com/~breadbox/software/tiny/teensy.html
/// http://dbp-consulting.com/tutorials/debugging/linuxProgramStartup.html
/// http://www.tldp.org/LDP/LG/issue84/hawk.html
/// 
/// 
/// LCOV - code coverage report
/// sudo apt-get install libgtest-dev
/// sudo apt - get install cmake # install cmake
/// cd / usr / src / gtest
/// sudo cmake CMakeLists.txt
/// sudo make
/// #copy or symlink libgtest.a and libgtest_main.a to your / usr / lib folder
/// sudo cp *.a /usr/lib
/// 
/// ------------------------------------------------------------------------------------------------------------------------------------------		
/// Codeblock build with cmake
/// cmake .. -G"CodeBlocks - Unix Makefiles"
/// /// </summary>

