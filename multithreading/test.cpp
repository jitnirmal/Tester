#include <iostream>
#include "ThreadException.h"
#include "atomics.h"

int main()
{
	TestAtomics();
	//TestThreadException();
	int i;
	std::cin >> i;
	return 0;
}