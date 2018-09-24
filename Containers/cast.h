#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_map>
#include <random>

void Test()
{
	auto seperator = []() {
		std::cout << "\n------------------------------------" << std::endl;
	};

	std::vector<int> vrates = { 1,2,3,4,5,6,7,8,9 };
	seperator();
	for (int i : vrates) {
		std::cout << " " << i;
	}
	seperator();

	for (auto& i : vrates) {
		i *= i;
	}

	for (const auto& i : vrates) {
		std::cout << " " << i;
	}
	seperator();

	std::map<std::string, int> mAge = { {"nirmal",37},{ "manjit",36 },{ "samar",8 },{ "seerat",4 } };
	for (const auto& record : mAge) {
		std::cout << " Name : " << record.first << " ,Age : " << record.second << std::endl;
	}
	seperator();

	std::unordered_map<std::string, int> uoAge = { { "nirmal",37 },{ "manjit",36 },{ "samar",8 } };
	uoAge["seerat"] = 4;
	for (const auto& record : uoAge) {
		std::cout << " Name : " << record.first << " ,Age : " << record.second << std::endl;
	}

	const auto searchStr = std::string{"seerat"};
	const auto& citer = uoAge.find(searchStr);
	if ( citer != uoAge.cend())
	{
		std::cout << "Age of " << searchStr << " is " << citer->second << std::endl;
	}
	

	seperator();
}

template<class ForwardIt, class Generator>
void n_generate(ForwardIt first, ForwardIt last, Generator g)
{
	while (first != last) {
		*first++ = g();
	}
}

template<class InputIt, class OutputIt, class UnaryOperation>
OutputIt n_transform(InputIt first1, InputIt last1, OutputIt d_first,	UnaryOperation unary_op)
{
	while (first1 != last1) {
		*d_first++ = unary_op(*first1++);
	}
	return d_first;
}

void vectorTest()
{
	class Object {
	public:
		Object(const int i) :Id(i) {}

		std::string test{"temporary string"};
		int Id;
	};

	constexpr int MAX_ITEMS{ 1000 };
	std::vector<int> vi(MAX_ITEMS,0);
	n_generate(std::begin(vi), std::end(vi), [n=0]()mutable { return (++n); });
	
	std::random_device rd;
	std::mt19937 g(rd());

	

	auto compare = [](const Object& a, const Object& b)
	{
		return a.Id < b.Id;
	};

	long long duration=0;
	int iterations = 10000;
	for (int i = 0; i < iterations; ++i)
	{
		std::shuffle(vi.begin(), vi.end(), g);
		std::list<int> lt;
		for (const auto& item : vi)
		{
			lt.push_back(item);
		}

		auto start = std::chrono::steady_clock::now();
		//std::sort(std::begin(vi), std::end(vi));
		lt.sort();
		auto end = std::chrono::steady_clock::now();
		duration += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	}
	std::cout << "Time took = " << duration/ iterations << " micro" << std::endl;


}

void func(int arr1[], int arr2[])
{
	auto print = [](int* arr, size_t length) {
		for (auto i = 0u; i < length; ++i)
		{
			std::cout << arr[i] << " ";
		}
	};

	size_t array_length = sizeof(arr1);

	for (auto i = 0u; i < array_length; ++i)
	{
		for (auto j = 0u; j < array_length; ++j)
		{
			if (i != j)
			{
				arr2[i] *= arr1[j];
			}
		}

	}
	print(arr2, array_length);
}
struct A {};
struct B : A {};
struct C {};

void testCast()
{
	int c = 10;       // 1 byte
	int *p = (int*)&c; // 4 bytes
	*p = 5;
	//Since this results in a 4-byte pointer ( a pointer to 4-byte datatype) pointing to 1 byte of allocated memory, 
	//writing to this pointer will either cause a run-time error or will overwrite some adjacent memory.
//	int *p = static_cast<int*>(&c); // 4 bytes


	A* a = new A;
	int i = 10;
	//a = (A*)(&i); // NO ERROR! FAIL!
    //a = static_cast<A*>(&i); //ERROR

	A* b = new B;
	B* b2 = static_cast<B*>(b); // NO ERROR! SMART!

//	C* c = (C*)(b); // NO ERROR! FAIL!

					//C* c = static_cast<C*>(b); ERROR! SMART!

}

int main(int argc, char *argv[])
{
	testCast();
	/*
	int A[] = { 2, 1, 5, 9 };
	int B[] = { 1, 1, 1, 1 };
	func(A, B);

	std::cout<<"testing Containers "<<std::endl;
	vectorTest();
//	Test();
*/
	std::map<std::string, int> mAge;
	std::cout << mAge["hello"] << std::endl;
	
	int i;
	std::cin >> i;
}
