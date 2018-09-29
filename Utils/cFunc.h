#pragma once  

#include <iostream>

void testArray() {
	int a[] = { 1, 2, 3, 4, 5, 6 };
	std::cout << (1 + 3)[a] << std::endl; // this is equivalent to a[4] --> 5
	std::cout << (a + 1)[2] << std::endl; // this is equivalent to a[3] --> 4
}

const int* getPointer() 
{
	const int * const p3 = new int(10);
	return p3;
}


int myAtoi(char *str)
{
	int res = 0; 
	for (int i = 0; str[i] != '\0'; ++i)
		res = res * 10 + str[i] - '0';
	return res;
}

class MTest
{
public:
	MTest() :_data(new int(20)),_val(30) {}

	const int* get() const
	{
		_val = 20;
		return _data;
	}
	void update() 
	{
		_val = 20;
		*_data = 200;
	}

	static int statVal()
	{
		return _x;
	}

private:
	int* _data;
	mutable int _val;
	static int _x;
};

int MTest::_x{ 0 };

void constOps()
{

	const int* p = getPointer();
	//*p = 20;
	p = new int(20);

	MTest mtest;
	const int* val = mtest.get();
	val = new int(10);

	MTest::statVal();

	const MTest mtest2;
	//mtest2.update(); this should give an error as operation is not const.
	
}
