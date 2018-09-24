#include <cstddef>
#include <vector>
/// <summary>
/// When an exception occurs, the stack is unwound from the point where the exception was thrown to the block where the exception is
/// handled, and this process involves the destruction of all local objects in all those stack frames.
/// If the destructor of an object that is being destroyed during this process throws an exception, another stack 
/// unwinding process should begin, which conflicts with the one already under way.Because of this, the program terminates abnormally.
/// 
/// Rule of thumb
/// 1. Use exceptions to indicate the errors that occur in constructors.
/// 2. Do not throw or let exceptions leave destructors.
/// 3. you should throw temporaries and catch exceptions by constant reference
/// 4. Prefer throwing either standard exceptions or your own exceptions derived from std::exception
/// 
/// a. std::logic_error : error in the program logic
///        --------- std::invalid_argument, std::out_of_range, and std::length_error
/// b. std::runtime_error : error beyond the scope of the program
///        --------- std::overflow_error, std::underflow_error, std::system_error
/// c. std::bad_ : represent various errors in a program,
///        --------- std::bad_alloc : failure to allocate memory
///        --------- std::bad_cast : failure to dynamically cast
///        --------- bad_function_call : failure to make function call
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