#include "Container.h"
#include "container_bmark.h"
#include "LockFree.h"
#include <iostream>
#include "Dependency.h"
#include "BGraph.h"
#include <cassert>
#include <memory>

int main()
{
	//testGraphTopologicalSort();
	/*constexpr auto SIZE{ 100u };

	std::vector<Expensive> expensiveTable(SIZE);
	std::generate(expensiveTable.begin(), expensiveTable.end(), [n = 0]() mutable { return Expensive(n++); });
	USet_tester<Expensive> EUSetTester(expensiveTable);

	std::vector<Cheap> cheapTable(SIZE);
	std::generate(cheapTable.begin(), cheapTable.end(), [n = 0]() mutable { return Cheap(n++); });
	Set_tester<Cheap> CUSetTester(cheapTable);*/
	//testThreadCoordination();
	//testAtomicThreadCoordination();
	//testLockFreeRingBuffer();
	//testBlockingQueue();
	//testThreadCreation();
	testDependencyGraph();
	int i;
	std::cin >> i;

}

