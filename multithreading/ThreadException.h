#pragma once

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>

/// <summary>
/// we assumed that multiple threads can throw exceptions and therefore need a container to hold them all.
/// and mutex to synchronize access to it
/// The std::exception_ptr pointer is a wrapper for an exception captured with std::current_exception()
/// The std::exception_ptr objects can be passed to other threads where they can be rethrown and caught in a try...catch block.
/// The std::rethrow_exception() is a function that takes std::exception_ptr as an argument and throws the exception object referred to by its argument.
/// </summary>

std::mutex                       g_mutex;
std::vector<std::exception_ptr>  g_exceptions;

void func1()
{
	throw std::exception("exception 1");
}

void func2()
{
	throw std::exception("exception 2");
}

/// <summary>
/// The std::current_exception() is a function that is typically used in a catch clause to
///  capture the current exception and create an instance of std::exception_ptr
/// </summary>
void thread_func1()
{
	try
	{
		func1();
	}
	catch (...)
	{
		std::lock_guard<std::mutex> lock(g_mutex);
		g_exceptions.push_back(std::current_exception());
	}
}

void thread_func2()
{
	try
	{
		func2();
	}
	catch (...)
	{
		std::lock_guard<std::mutex> lock(g_mutex);
		g_exceptions.push_back(std::current_exception());
	}
}

void TestThreadException()
{
	g_exceptions.clear();

	std::thread t1(thread_func1);
	std::thread t2(thread_func2);
	t1.join();
	t2.join();

	for (auto const & e : g_exceptions)
	{
		try
		{
			if (e != nullptr)
				std::rethrow_exception(e);
		}
		catch (std::exception const & ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
}