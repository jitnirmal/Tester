#include <iostream>
#include <memory>
#include "move.h"
#include "MyString.h"
#include "cFunc.h"


void TestRValue()
{
	int&& rvalueReference = 25 + 17;
	int* pointerToRvalueReference = &rvalueReference;
	*pointerToRvalueReference = 23;
}


int main(int argc, char *argv[])
{
	//std::shared_ptr<int> sp();
	//std::cout<<"testing Patterns "<<std::endl;
//	testMultiply();
//	TestRValue();
//	TestMove();
//	TestString();
//	testMoveMemoryBlock();
	//testStatic();
	//testArray();
	constOps();
	
}
