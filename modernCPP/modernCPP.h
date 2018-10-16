#pragma once
#include <iostream>
#include <vector>

/// <summary>
/// SPECIAL Operatons
///			a. Move operations are generated only for classes lacking explicitly declared move operations, copy operations, and a destructor.
///			b. The copy constructor is generated only for classes lacking an explicitly declared copy constructor, and it’s deleted if a move operation is declared.
///			c. The copy assignment operator is generated only for classes lacking an explicitly declared copy assignment operator, 
///				and it’s deleted if a move operation is declared.
///			d. Generation of the copy operations in classes with an explicitly declared destructor is deprecated.
///			e. Member function templates never suppress generation of special member functions. 
/// 
/// Unique Pointer
///		a. std::unique_ptr is a small, fast, move-only smart pointer for managing resources with exclusive - ownership semantics.
///		b. By default, resource destruction takes place via delete, but custom deleters can be specified.
///			Stateful deleters and function pointers as deleters increase the size of std::unique_ptr objects.
///		c. Converting a std::unique_ptr to a std::shared_ptr is easy.
/// 
/// Shared Pointer
///		a. Compared to std::unique_ptr, std::shared_ptr objects are typically twice as big, incur overhead for control blocks,
///			 and require atomic reference count manipulations.
///		b. Default resource destruction is via delete, but custom deleters are supported. The type of the deleter has no effect on the type of the std::shared_ptr.
/// 
/// std::make_shared
///		a. avoid potential resource leak
///		b. performance : 
/// Compared to direct use of new, make functions eliminate source code duplication, improve exception safety, and, for std::make_shared and std::allocate_shared, 
///			generate code that’s smaller and faster.
///		Situations where use of make functions is inappropriate include the need to specify custom deleters, classes with custom memory management
/// 
/// STD MOVE
///		a. Apply std::move to rvalue references and std::forward to universal references the last time each is used.
///			 Do the same thing for rvalue references and universal references being returned from functions that return by value.
///			Never apply std::move or std::forward to local objects if they would otherwise be eligible for the return value optimization.
/// Perfect forwarding fails when template type deduction fails or when it deduces the wrong type
///	The kinds of arguments that lead to perfect forwarding failure are braced initializers, null pointers expressed as 0 or NULL, declaration - only integral const
/// static data members, template and overloaded function names, and bitfields
/// 
/// /// </summary>
