#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <array>
#include <cassert>
#include <memory>
/// <summary>
/// 
/// CALLABLES : client code passes an entity that must be “called.”
/// a. Pointer-to-function types
/// b. Class types with an overloaded operator() (sometimes called functors), 
/// c. lambdas
/// </summary>

//http://bannalia.blogspot.com/2016/07/passing-capturing-c-lambda-functions-as.html

template<typename Iter, typename Callable>
void foreach(Iter current, Iter end, Callable op)
{
	while (current != end) {        
		op(*current);               
		++current;                  
	}
}

void func(int i)
{
	std::cout << "func() called for:  " << i << "\n";
}

class FuncObj {
public:
	void operator() (int i) const {   
		std::cout << "FuncObj::op() called for:      " << i << "\n";
	}
	// Note that when defining operator(), you should usually define it as a constant member function.
	// Otherwise, subtle error messages can occur when frameworks or libraries expect this call not to change the state of the passed object
};

void testCallable()
{
	std::vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19 };
	
	foreach(primes.begin(), primes.end(),func);   // function as callable (decays to pointer)
	foreach(primes.begin(), primes.end(), &func); // function pointer as callable
	foreach(primes.begin(), primes.end(),FuncObj());
	foreach(primes.begin(), primes.end(), [](int i) { 
		std::cout << "lambda called for:      " << i << "\n";
	});
}