#include <iostream>
#include "ThreadedQ.h"
#include "BlockingQueue.h"
#include "WaitFree.h"
#include "RingBuffer.h"
#include "ObjectPool.h"

int main()
{
	TestBlockingQueue();
	testWaitFree();
	//TestThreadedQ();
	//TestAllocator();
	//TestAllocator();
	TestRingBuffer();
	int i;
	std::cin >> i;
	return 0;
}