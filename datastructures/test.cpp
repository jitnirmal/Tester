#include <iostream>
#include <thread>
#include <chrono>
#include "sort.h"
#include "QSort.h"
#include "c_linked_list.h"
#include "LinkedList.h"
/*
#include "MyWeakPointer.h"
#include "LinkedList.h"
#include "MyUniquePtr.h"
#include "BinaryTree.h"
#include "smartPointers.h"
#include "MyHashTable.h"
#include <iostream> 
#include <thread> 
#include <utility>

void TestThread()
{
	// 2 errors on thread lifetime
	//http://www.modernescpp.com/index.php/threads-lifetime
	//https://github.com/lefticus/cppbestpractices
		std::thread t([] {std::cout << std::this_thread::get_id(); });
		std::thread t2([] {std::cout << std::this_thread::get_id(); });

		t.join();
		
		t = std::move(t2);
		std::cout << std::boolalpha << "t2.joinable(): " << t2.joinable() << std::endl;

		t2.join();

}

*/

int main(int argc, char *argv[])
{
	int i = 0;
	testCList();
	testLinkList();
//	testSort();
//	printf("%d %d %d\n", i++, i++, i++);


//	std::cout<<"testing multithreading "<<std::endl;
	//testWeakPointer();
	//	TestHashTable();
	//Tes_C_tUtils();
//	TestUtils();
//	Tes_checkUniqueString();
//	TestLinkedList();
//	TestUniquePtr();
	//TestThread();
//	TestBinaryTree();
//	testWeakPointer();
//	testSmartPointers();
}
