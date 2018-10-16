#pragma once
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>




/// <summary>
/// Shared memory is typically the fastest form of interprocess communication. 
///		It provides a memory area that is shared between processes. 
///		One process can write data to the area and another process can read it.
///  Boost.Interprocess provides the class boost::interprocess::allocator
///			-- boost::interprocess::basic_string
///			-- boost::interprocess::vector
///			-- boost::interprocess::map
/// </summary>


using namespace boost::interprocess;

void testSharedmem()
{
	managed_shared_memory managed_shm{ open_or_create, "shm", 1024 };
	int *i = managed_shm.find_or_construct<int>("Integer")(0);
	interprocess_mutex *mtx =
		managed_shm.find_or_construct<interprocess_mutex>("mtx")();
	interprocess_condition *cnd =
		managed_shm.find_or_construct<interprocess_condition>("cnd")();
	scoped_lock<interprocess_mutex> lock{ *mtx };
	while (*i < 10)
	{
		if (*i % 2 == 0)
		{
			++(*i);
			cnd->notify_all();
			cnd->wait(lock);
		}
		else
		{
			std::cout << *i << std::endl;
			++(*i);
			cnd->notify_all();
			cnd->wait(lock);
		}
	}
	cnd->notify_all();
	shared_memory_object::remove("shm");
}