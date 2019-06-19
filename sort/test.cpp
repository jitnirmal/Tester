#include "perf.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "sort.h"
#include "QSort.h"
#include "heap.h"
#include "redix.h"
#include "merge.h"
#include "bsearch.h"


int main(int argc, char *argv[])
{
	int i = 0;
	printHeader();
	TestHeapPerformance();
	TestMergeSortPerformance();
	TestQSortPerformance();
	TestRedixSortPerformance();
	TestHashTablePerformance();
}
