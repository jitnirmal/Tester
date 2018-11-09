#pragma once
#include <vector>

#include <cstdint>
/// <summary>
/// prob 1
/// </summary>
/// <param name="p"></param>
void processPtr(int * p)
{
	p = 0;
	//*p=0; // this will actually change the value of pointed variable.
}
void testPointer1()
{
	int* p = new int(20);
	processPtr(p);
	std::cout << "pointer val is : "<<*p << std::endl;
}

/// <summary>
/// prob 2
/// </summary>
/// <param name="p"></param>
void testPointer2()
{
	int *p = new int(20);
	int64_t pInt =  reinterpret_cast<int64_t>(p);
	//10467280
	auto result = pInt & 1;
	
	if ((pInt & 1) != 1)
	{
		delete p;
	}
}

/// <summary>
/// prob3
/// </summary>
// replace operator new and delete to log allocations

void testAllocations()
{
	struct A {
		std::shared_ptr<int> spx = { new int(10), [](int* p) {} };
	};

	// sizeof(A) - 8
	std::vector<std::shared_ptr<A>> v; // allocates 8 bytes.
	v.emplace_back(new A);
	/*
	Allocating 8 bytes, 0003FA28 , 5    // default vector allocation
	Allocating 8 bytes, 0003F9F0, 2     //  new A
	Allocating 4 bytes, 000363B8		//  new int
	Allocating 16 bytes, 0003E608, 1
	Allocating 8 bytes, 0003F980 , 4
	Allocating 16 bytes, 000364C8, 3

	Deallocating 0003E608
	Deallocating 0003F9F0
	Deallocating 000364C8
	Deallocating 0003F980
	Deallocating 0003FA28
	*/
}

void testAllocations1()
{
	struct A {
		std::shared_ptr<int> spx = { new int(10), [](int* p) { delete p; } };
	};

	A a;
	// Allocating 4 bytes,  0085FC98
	// Allocating 16 bytes, 00856030
	// Deallocating			0085FC98 // delete int
	// Deallocating			00856030 // delete RC
}

void testAllocations2()
{
	auto a = std::make_shared<int>(10);
	//Allocating 16 bytes, 0028F048
	//Deallocating 0028F048

	std::cout << sizeof(a) << std::endl;
	//8 bytes
}

void testType()
{
	std::vector<int> v;
	auto result = std::move(v);
	std::cout << "type= " << typeid(result).name() << std::endl;
	//type= class std::vector<int,class std::allocator<int> >
}


/// <summary>
/// the dreaded multiple inheritance diamond
/// </summary>
class AA {
public:
	AA() { puts("AA const"); }
	int aa;
};
class BB : virtual public AA {
public:
	BB() { puts("BB const"); }
};
class CC : public AA {
public:
	CC() { puts("CC const"); }
};
class DD : public BB, public CC {
public:
	DD() { puts("DD const"); }
};

void testDiamondInheritance()
{
	DD dd; 
	/// <summary>
	/// AA const
	/// BB const
	/// AA const
	/// CC const
	/// DD const
	/// </summary>

	// dd.aa = 20; // till the time we dont use aa, it is not compile/run error
}


void TestCPP()
{
//	testDiamondInheritance();
//	testPointer1();
//	testPointer2();
//	testAllocations();
	testAllocations2();
//	testType();

}