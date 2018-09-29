#include <iostream>
#include <chrono>
#include <functional>
#include <type_traits>
#pragma pack (1)
struct SampleStructPack1
{
	bool flag;
	unsigned int timeout;
};
#pragma pack(0)

#pragma pack (2)
struct SampleStructPack2
{
	bool flag;
	unsigned int timeout;
};
#pragma pack(0)

#pragma pack (4)
struct SampleStructPack4
{
	bool flag;
	unsigned int timeout;
};
#pragma pack(0)


struct SampleStruct
{
	bool flag;
	unsigned int timeout;
};

static const long MAX_ELEMENTS = 100000;
using namespace std;
using namespace std::chrono;

template<typename T>
void allocate()
{
	T elements[MAX_ELEMENTS];
	cout << typeid(T).name()<<" : " << sizeof(elements) << " bytes allocated";
}

void test(int i, double d, std::string s)
{
	std::cout << "i=" << i << " , d=" << d << " ,s=" << s << std::endl;
}

template<typename ... Args>
void printElaspedTime(std::function<void()> func, Args&& ... args)
{
	auto begin = high_resolution_clock::now();
	func(std::forward<Args>(args)...);
	cout << " in " << duration_cast<nanoseconds>(high_resolution_clock::now() - begin).count() << " nanosecond" << endl;
}



template<class Func, class... Args>
void run_test(Func&& func, Args&&... args)
{
	auto begin = high_resolution_clock::now();
	func(std::forward<Args>(args)...);
	cout << " in " << duration_cast<nanoseconds>(high_resolution_clock::now() - begin).count() << " nanoseconds" << endl;
}

void TestPack()
{
//	printElaspedTime(allocate<SampleStructPack1>);
//	printElaspedTime(allocate<SampleStructPack2>);
//	printElaspedTime(allocate<SampleStructPack4>);
	run_test(test,1,2.f,"nirmal");
}