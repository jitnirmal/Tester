#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <memory>
#include <utility>
#include <cassert>
#include <algorithm>
class Object
{
public:
	Object(int const i, double const d, std::string& const str) :
		iData(i), dData(d), strData(str) {}
	void print()
	{
		std::cout << "i : " << iData << " d : " << dData << "str : " << strData << std::endl;
	}
private:
	int iData;
	double dData;
	std::string strData;
};

void testUnique()
{
	Object* obj1 = new Object(2,2.0,std::to_string(2));
	auto obj2 = std::make_unique<Object>(2, 2.0, std::to_string(2));
	obj2->print();
	auto obj3 = std::move(obj2);

}

void constCorrectness()
{
	// both data and pointer can be changed
	int* parent = new int(10);
	*parent = 30;
	parent = new int(20);

	// data ins const and pointer can be changed
	const int* p1 = new int(10);
	//*p1 = 30; // this is error because data is constant
	p1 = new int(20);

	// data ins const and pointer can be changed (same as above)
	int const* p2 = new int(10);
	//*p2 = 30; // this is error because data is constant
	p2 = new int(20);

	// data is const and pointer is const
	int const* const p3 = new int(10);
	//*p3 = 30; // this is error because data is constant
	//p3 = new int(20); //this is error because pointer is const as well
	
}



int possibleBoardsTickTackToe() {
	std::string board = "XXXXXOOOO";
	std::sort(std::begin(board), std::end(board));
	do {
		std::cout << board << '\n';
	} while (std::next_permutation(std::begin(board), std::end(board));
	return 0;
}

int main(int argc, char *argv[])
{
	std::cout<<"testing multithreading "<<std::endl;
	//TestException();
	//testUnique();
	constCorrectness();
}
