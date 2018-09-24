#pragma once
#include <memory>
#include <iostream>


struct ClassB;
struct ClassD;

struct ClassA {
    std::shared_ptr<ClassB> B;
	~ClassA() { puts("~ClassA"); }
};

struct ClassB {
	std::shared_ptr<ClassA> A;
	~ClassB() { puts("~ClassB"); }
};

void TestCyclicSP() {
	{
		std::shared_ptr<ClassA> spA{ new ClassA{} };
		std::shared_ptr<ClassB> spB{ new ClassB{} };
		spA->B = spB;
		spB->A = spA;
		std::cout << spA.use_count() << ' ' << spA->B.use_count() << ' ' << spB.use_count() << ' ' << spB->A.use_count() << std::endl;
	}
};



struct ClassC {
	std::weak_ptr<ClassD> D;
	~ClassC() { puts("~ClassC"); }
};

struct ClassD {
	std::weak_ptr<ClassC> C;
	~ClassD() { puts("~ClassD"); }
};

void TestCyclicWP() {
	{
		std::shared_ptr<ClassC> spC{ new ClassC{} };
		std::shared_ptr<ClassD> spD{ new ClassD{} };
		spC->D = spD;
		spD->C = spC;
		
		if (auto spt = spC->D.lock()) { // Has to be copied into a shared_ptr before usage
			std::cout << spt.use_count() << "\n";
		}
		if (auto spt = spD->C.lock()) { // Has to be copied into a shared_ptr before usage
			std::cout << spt.use_count() << "\n";
		}
	}
}

std::weak_ptr<int> wp;
void observe()
{
	std::cout << "use_count == " << wp.use_count() << ": ";
	if (auto spt = wp.lock()) { // Has to be copied into a shared_ptr before usage
		std::cout << *spt << "\n";
	}
	else {
		std::cout << "wp is expired\n";
	}
}

void testWPObserve()
{
	{
		auto sp = std::make_shared<int>(42);
		wp = sp;

		observe();
	}

	observe();
}

void testWeakPointer()
{
	TestCyclicSP(); 
	TestCyclicWP();
//	testWPObserve();

}
