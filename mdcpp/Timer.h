#pragma once

#include <chrono>
#include <iostream>
#include <iostream>

struct A
{
	A(int x) :xval(x) {}
	int xval;
};
struct Test
{
	void Display(int x, double d, std::string&& str, A&& a)
	{
		std::cout << "x=" << x <<", d="<<d<<" ,str="<<str<<" ,a.xval="<<a.xval << std::endl;
	}
};

void func(int const count = 100000000)
{
		for (int i = 0; i < count; ++i);
}

template <typename Time = std::chrono::microseconds,
	typename Clock = std::chrono::high_resolution_clock>
	struct perf_timer
{
	template <typename F, typename... Args>
	static Time duration(F&& f, Args... args)
	{
		auto start = Clock::now();
		std::forward<F>(f)(std::forward<Args>(args)...);
		auto end = Clock::now();
		return std::chrono::duration_cast<Time>(end - start);
	}
};


void TestTimer()
{
	auto t1 = perf_timer<std::chrono::nanoseconds>::duration(func, 100000000);
	std::cout <<"time taken in nanosecs : "<< t1.count() << std::endl;

	Test t;
	auto t2 = perf_timer<std::chrono::nanoseconds>::duration(std::mem_fn(&Test::Display),&t,1,2.4f,"test",A(4));
	std::cout << "time taken in nanosecs : " << t2.count() << std::endl;

}