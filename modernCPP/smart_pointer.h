#pragma once
#include <iostream>
#include <memory>

struct ObjectSFT : public std::enable_shared_from_this<ObjectSFT> {
	ObjectSFT() { std::cout << "ObjectSFT::ObjectSFT\n"; }
	~ObjectSFT() { std::cout << "ObjectSFT::~ObjectSFT\n"; }
	std::shared_ptr<ObjectSFT> getFoo() { return shared_from_this(); }
};

void testSharedFromThis() {
	//ObjectSFT *f = new ObjectSFT;
	std::shared_ptr<ObjectSFT> pf1;

	{
		std::shared_ptr<ObjectSFT> pf2(new ObjectSFT);
		pf1 = pf2->getFoo();  // shares ownership of object with pf2
	}

	std::cout << "pf2 is gone\n";
}

void testSmartPointer()
{
	testSharedFromThis();
}