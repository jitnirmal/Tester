#pragma once

#include <iostream>
using namespace std;
#include <map>

/// <summary>
/// 1. empty destructors
///		writing an empty destructor prevents the compiler from implementing certain optimizations.
///		--copying an array of a trivial class with an empty destructor yields the same, non-optimized, assembler code as copying with a handcrafted for loop
///		-- However, if we remove or declare the destructor default, the compiler optimize std::copy to utilize memmove instead of a loop
/// </summary>


void TestPerformance2()
{
	
}

