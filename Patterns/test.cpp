#include <iostream>
#include "Factory.h"
#include "Visitor.h"
#include "Observer.h"



void testFP(std::function<void(int)> function)
{
	auto x = { 10 };
	function(10);
}

void TestFactory()
{
	auto factory = ProductFactory{};
	auto stockSP = factory.Create(typeid(Stock));
}


int main(int argc, char *argv[])
{
	testObserver();
}
