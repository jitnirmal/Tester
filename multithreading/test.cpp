#include <iostream>
#include "ThreadException.h"
#include "atomics.h"

#include "ThreadPool.h"
int main()
{
	//TestAtomics();
	TestThreadPool();
	//TestThreadException();
	int i;
	std::cin >> i;
	return 0;
}