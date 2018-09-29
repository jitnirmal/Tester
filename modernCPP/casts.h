#include <cstddef>

struct Parent {
	const int value{ 100 };
	virtual ~Parent() {}
};

struct Child : public Parent {
};
struct Other {
	virtual ~Other() {}
};


void testConstCast()
{
	const Child c;
	//c.value = 100;
	// constness is compiler restriction.. and it can be removed with const
	*const_cast<int*>(&(const_cast<Child*>(&c)->value)) = 300;
	std::cout << c.value << std::endl;
}

void testStaticCast()
{
	Parent* parent = new Child();
	Other* other = new Other();

	Child* child = static_cast<Child*>(parent);

// This will give invalid Child error
//	Child* child = static_cast<Child*>(other);

}

void testDynamicCast()
{

	auto getChild = [](Parent& p) {
		Child& c = dynamic_cast<Child&>(p);
		return c;
	};

	

	Parent* parent = new Child();
	Other* other = new Other();
	Child* child = dynamic_cast<Child*>(other);
	if (child == nullptr)
	{
		// with pointers it does not throw
	}

	
	Child& c = getChild(*parent);

	Other o;
	try {
		Child& c2 = dynamic_cast<Child&>(*parent); // good case
		//taking reference of incompatible types throws error.
		Child& c3 = dynamic_cast<Child&>(o); // this will throw
	}
	catch (const std::bad_cast& e)
	{
		std::cout << e.what() << '\n';
	}

}

void testCasts()
{
	testStaticCast();
	testDynamicCast();
	testConstCast();
}