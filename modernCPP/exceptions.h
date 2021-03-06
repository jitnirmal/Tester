#include <cstddef>
#include <vector>
/// <summary>
/// When an exception occurs, the stack is unwound from the point where the exception was thrown to the block where the exception is
/// handled, and this process involves the destruction of all local objects in all those stack frames.
/// If the destructor of an object that is being destroyed during this process throws an exception, another stack 
/// unwinding process should begin, which conflicts with the one already under way.Because of this, the program terminates abnormally.
/// 
/// Exception-safe functions offer one of three guarantees: 
/// 1. basic guarantee - if an exception is thrown, everything in the program remains in a valid state.
///							No objects or data structures become corrupted, and all objects are in an 
///							internally consistent state(e.g., all class invariants are satisfied).
///							However, the exact state of the program may not be predictable.
///						For ex - if DB connection throws, DB connection goes to uninitialized, Rety, Error state
/// 2. strong guarantee - if an exception is thrown, the state of the program is unchanged. 
///							Calls to such functions are atomic in the sense that if they succeed, they
///							succeed completely, and if they fail, the program state is as if they�d never been called.
/// 3. the nothrow guarantee - promise never to throw exceptions, because they always do what they promise to do.
/// 
/// int doSomething() noexcept  // This doesn�t say that doSomething will never throw an exception; it says
///						 that if doSomething throws an exception, it�s a serious error, and the terminate function should be called.�
/// 
	
/// 
/// 
/// Rule of thumb
/// 1. Use exceptions to indicate the errors that occur in constructors.
/// 2. Do not throw or let exceptions leave destructors.
/// 3. you should throw temporaries and catch exceptions by constant reference
/// 4. Prefer throwing either standard exceptions or your own exceptions derived from std::exception
/// 
/// a. std::logic_error : error in the program logic
///        --------- std::invalid_argument, std::out_of_range, and std::length_error, 
/// b. std::runtime_error : error beyond the scope of the program
///        --------- std::overflow_error, std::underflow_error, std::system_error
/// c. std::bad_ : represent various errors in a program,
///        --------- std::bad_alloc : failure to allocate memory
///        --------- std::bad_cast : failure to dynamically cast
///        --------- bad_function_call : failure to make function call
/// d. When throwing an exception
///		--- throw an object by value. Avoid throwing a pointer, because if you throw a pointer, you need to deal with memory management issues
///    ---  Throwing by value - the compiler itself takes responsibility for the intricate process of managing memory for the exception object.
///    ---  Catch by reference - Catching a plain value by value results in slicing at the catch site and 2 copies of the thrown object are made
///	   --- NOTE : Regardless of whether the exception is caught by value or by reference, a copy
///				of thrownObject will be made, and it is the copy that is passed to the catch clause.
///				This must be the case, because thrownObject will go out	of scope once control leaves throwingFunction, and when  
///				thrownObject goes out of scope, its destructor will be called.
///    ---  When rethrowing an exception e, prefer throw; instead of throw e; because it preserves polymorphism of the rethrown object.
/// e. Prefer rethrowing some exception
///				1. catch (Base& b) {... // handle the exception  throw; } //rethrows the current exception
///				2. catch (Base& b) {	... // handle the exception	throw b;} // propagate a copy of the exception
///					2, is worse in performance and cause derived class exception to be passed as base.
/// 
/// 
///	Performance : 1. If you know that no part of your program uses try, throw, or catch, and you also know that no library
///			with which you�ll link uses try, throw, or catch, you might as well compile without exception - handling support 
///			and save yourself the size and speed penalty you�d otherwise probably be assessed for a feature you�re not using.
///			-fno-exceptions : Note also that stack unwinding will not be performed if an exception is not handled; 
///					a) All exception handling in STL libraries are removed; throws are replaced with abort() calls
///					b) Stack unwind data and code is removed. This saves some code space, and may make register allocation 
///					marginally easier for the compiler (but I doubt it'll have much performance impact). 
///					Notably, however, if an exception is thrown, and the library tries to unwind through 
///					-fno-exceptions code, it will abort at that point, as there is no unwind data.
///			2. A second cost of exception-handling arises from try blocks, and you pay it whenever you use one, 
///					a) expect your overall code size to increase by 5 - 10 % 
///					b) and your runtime to go up by a similar amount if you use try blocks.
///					This assumes no exceptions are thrown; what we�re discussing here is just the
///					cost of having try blocks in your programs.To minimize this cost, you should avoid unnecessary try blocks.
///			3. 	Returning from a function by throwing an exception may be 3 times slower
///				
///			

/// </summary>
struct A {
	~A() noexcept(false)
	{
		std::cout << "~A throws" << std::endl;
		throw std::logic_error("A exception");
	}
};

struct B {
	~B() noexcept(false)
	{
		std::cout << "~B throws" << std::endl;
		throw std::logic_error("B exception");
	}
};

struct C{
	/// <summary>
	/// This function is supposed to be calling terminate as we defined it noexcept(true)
	/// and exception is escaped from this function
	/// </summary>
	void Test() noexcept {
		std::cout << "at runtime this calls std::terminate" << std::endl;
		throw std::logic_error("C exception");
	}

};
void TestExceptionsTerminate()
{
	{
		std::cout << "starts " << std::endl;
		try
		{
			//A a;
			//B b;
			C c;
			c.Test();
		}
		catch (std::exception const & e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "uunknown exception " << std::endl;
		}
		std::cout << "ends " << std::endl;
	}
}


/// <summary>
/// Exceptions and error codes are not mutually exclusive. 
/// Exceptions should be used only for transferring the control flow in exceptional situations, 
/// not for controlling the data flow in a program.
/// </summary>
class simple_error : public std::exception
{
	const char* what() const noexcept override
	{
		return "simple error";
	}
};

class simple_logic_error : public std::logic_error
{
public:
	simple_logic_error() :
		logic_error("simple logic error")
	{}
};

auto excpPrinter = [](std::exception const & ex)
{
	std::cout << "exception happened " << ex.what() << std::endl;
};

void throwing_func()
{
	throw std::system_error(std::make_error_code(std::errc::timed_out));
}

void TestException()
{

	std::vector<int> v = { 1,2,3,4 };
	v.push_back(4);
	try {
		throwing_func();
	}
	catch (std::system_error const& ex)
	{
		excpPrinter(ex);
	}
	catch (std::runtime_error const& ex)
	{
		excpPrinter(ex);
	}
	catch (std::exception const& ex)
	{
		excpPrinter(ex);
	}
	catch (...)
	{
		std::cout << "unknown exception" << std::endl;
	}
}

/// <summary>
/// The strong exception guarantee specifies that either an operation is completed successfully, 
/// or is completed with an exception that leaves the program in the same state it was before the operation started.
/// This ensures commit - or -rollback semantics.
/// Many standard containers provide some of their operations with a strong exception guarantee.
/// An example is vector's push_back() method.
/// However, in order to preserve its strong exception guarantee, this can only be done if the move constructor or assignment
/// operator does not throw exceptions.If they do, then the copy constructor or assignment operator must be used.
/// The std::move_if_noexcept() utility function does this if the move constructor of its type argument is marked with noexcept
/// 
/// SO ENSURE TO MARK MOVE CONSTRUCTORS AND ASSIGNMENTS TO BE NOEXCEPT TO MAKE USE OF CONTAINER STRONG EXCEPTION guarantee
/// </summary>
/// 

struct FOO
{

};