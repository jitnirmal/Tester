#pragma once
#include <iostream>
#include <vector>

/// <summary> ITEM -1 / Vect
/// 1. Be const correct. In particular, use const_iterator when you are not modifying the contents of a container.
/// 2. Prefer comparing iterators with != , not <.
/// 3. Practice reuse : Prefer reusing existing algorithms, particularly standard algorithms(e.g.,for_each), instead of crafting your own loops.
///			a. v.at(0)  - std::out_of_range while v[0] is not determinstic if 0 index is empty
///			b. calling v[0] with only reserve, without push_back will crash
///			c. v.reserve(2); assert(v.capacity() == 2); this may fail.. so dont check this way
/// </summary>

/// <summary>2. The Joys and Sorrows of sprintf
/// 1. Ease of use and clarity. --> void PrettyFormat(int i, char* buf) { sprintf(buf, "%4d", i);}
/// 2. Maximum efficiency - ability to directly use existing buffers (no dynamic memory allocations)
/// 
/// Issues
/// a. Length safety (destination buffer doesn't happen to be big enough for the whole output)
/// b. Type-safe : 
///				a. sprintf(buf, "%4c", i); //silently reinterpret the first byte of i as a char value
///				b. sprintf(buf, "%4s", i); //sprintf will silently reinterpret the integer as a pointer to char
///						immediate or intermittent crash
/// c. Hard to use with templates
///			Templatability. It's very hard to use sprintf in a template
///			template<typename T> void PrettyFormat(T value, char* buf) {sprintf(buf, "%/*what goes here?*/", value); }
/// 
/// Alternatives:
/// -------------
/// 1. use snprintf (covers the buffer overrun problems)
/// 2. use std::stringstream
///		template<typename T> void PrettyFormat(T value, string& s) {ostringstream temp; 	temp << setw(4) << value;	s = temp.str();}
/// 3. boost::lexical_cast
/// </summary>

/// <summary>
/// placement new,
/// </summary>
template <class T1, class T2>
void construct(T1* p, const T2& value) {
	new (p) T1(value);
}

void TestExceptionalCPP()
{
}

