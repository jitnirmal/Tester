#include <iostream>
#include "ASyncParallel.h"
#include "SyncIterative.h"
#include "SyncParallel.h"
#include "SyncTCPClient.h"



int main()
{
	std::vector<std::thread> services;
	services.push_back(std::thread(TestAsyncParallel));
	//services.push_back(std::thread(TestSyncIterative));
	//services.push_back(std::thread(TestSyncParallel));
	services.push_back(std::thread(TestSyncTCPClient));
	

	for (auto& service : services)
	{
		service.join();
	}
	return 0;
}