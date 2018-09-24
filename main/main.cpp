#include <iostream>
#include <map>
using namespace std;
//https://www.reddit.com/r/cpp/comments/4befx3/suggestions_for_free_online_c_quizzes_and_tests/
bool default_constructed = false;
bool constructed = false;
bool assigned = false;




//http://www.gotw.ca/gotw/054.htm

class C {
public:
	C() { default_constructed = true; }
	C(int) { constructed = true; }
	C& operator=(const C&) { assigned = true; return *this; }
};

void mapInsertion() {
	map<int, C> m;
	m[7] = C(1);
	cout << default_constructed << constructed << assigned << std::endl; //111

	default_constructed = false; constructed = false; assigned = false;
	m.insert(pair<int, C>(7, C(1)));
	cout << default_constructed << constructed << assigned << std::endl; // 010

	default_constructed = false; constructed = false; assigned = false;
	m.emplace(7, C(1));
	cout << default_constructed << constructed << assigned << std::endl; //010
																		 // http://cppquiz.org/quiz/question/208?result=OK&answer=111&did_answer=Answer
}
//--------------------------------------------------------------------------------------------------

struct X {
	X() { std::cout << "a"; }
	X(const X &x) { std::cout << "b"; }
	const X &operator=(const X &x) {
		std::cout << "c";
		return *this;
	}
};

void testX() {
	X x;
	X y(x);
	X z = y;
	z = x;
}
//--------------------------------------------------------------------------------------------------
// abbc
//--------------------------------------------------------------------------------------------------

void testInteger() {
	int i = 42;
	int j = 1;
	std::cout << i / --j;
}
//--------------------------------------------------------------------------------------------------
// division by zero 
//--------------------------------------------------------------------------------------------------
struct A {
	virtual int fn(int i = 5) const { return i + 1; }
};

struct B : A {
	virtual int fn(int i = 7) const override { return i + 2; }
};


void run(const A& a) {
	std::cout << a.fn(1) << a.fn();
}

void testClass() {
	run(B());
}
//--------------------------------------------------------------------------------------------------
// 3, 7
//The implementation doesn't care about the "virtuality" of a function when determining the default argument,
//but instead uses the static type of the the referenced object. Thus, the default argument 5 from A::fn 
//will be used even if B::fn is called, and 7 is printed.
//--------------------------------------------------------------------------------------------------

template <class T> void f(T &i) { std::cout << 1; }

template <> void f(const int &i) { std::cout << 2; }

void testTemplate1() {
	int i = 42;
	f(i);
}
//--------------------------------------------------------------------------------------------------
// 1
//--------------------------------------------------------------------------------------------------
template <template <typename> class>
struct P {
	P() { std::cout << "1"; }
};

template <typename>
struct Q {};

template <typename T>
using R = Q<T>;

template <>
struct P<Q> {
	P() { std::cout << "2"; }
};

void testTemplate2() {
	P<Q> x1;
	P<R> x2;
}
//--------------------------------------------------------------------------------------------------
// 2 1
//http://cppquiz.org/quiz/question/117?result=OK&answer=21&did_answer=Answer
//--------------------------------------------------------------------------------------------------
/*
namespace AA {
extern "C" { int x; }
};

namespace BB {
extern "C" { int x; }
};

int AA::x = 0;

void testExtern() {
std::cout << BB::x;
AA::x = 1;
std::cout << BB::x;
}
*/
//--------------------------------------------------------------------------------------------------
// compilation error
//A::x and B::x actually refer to the same variable, and int x; is a definition, not a declaration
//--------------------------------------------------------------------------------------------------
struct XX {
	XX() { std::cout << "X"; }
};

struct YY {
	YY(const XX &x) { std::cout << "Y"; }
	void f() { std::cout << "f"; }
};

void testStruct() {
	YY y(XX());
	y.f();
}

int main()
{
	testStruct();
}