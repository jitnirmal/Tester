#pragma once
#include <iostream>
#include <vector>
struct Object
{
	Object() = default;
	
	Object(int i, double d, std::string& s, std::vector<int>& v) :
		_i(i), _d(d), _s(s), _v(v) 
	{
		std::cout << "Object(&)" << std::endl;
	}
	
	Object(int i, double d, std::string&& s, std::vector<int>&& v) :
		_i(i), _d(d), _s(s), _v(v) 
	{
		std::cout << "Object(&&)" << std::endl;
	}

	int _i;
	double _d;
	std::string _s;
	std::vector<int> _v;

};

struct ObjectContainer
{
	template<typename ... Args>
	// forwarding reference --> universal reference (lvalue reference or rvalue reference)
	void AddObject(Args&& ... args)
	{
		//v.emplace_back(args...);
		v.emplace_back(std::forward<Args>(args)...);
	}
private:
	std::vector<Object> v;
};

void TestPerfectForwarding()
{
	std::vector<int> v = { 1,2,3,4,5 };
	std::string s = "nirmal";

	ObjectContainer oc;
	oc.AddObject(1,2.f,"nirmal",std::move(v)); // Object(&&)
	oc.AddObject(1, 2.f, s, std::move(v)); // Object(&)
	oc.AddObject(1, 2.f, s, v); // Object(&)
	//oc.AddObject(1, 2.f, "test", v); // this will give compilation error
}


void TestMove()
{
	int x = 10;
	int y = std::move(x);
	/// <summary>
	/// y becomes 10, but x remains 10 as well..
	/// </summary>

	std::string str1 = "nirmal";
	std::string str2 = std::move(str1);
	/// <summary>
	/// str1 = "" , str = "nirmal";
	/// </summary>

	std::vector<int> v1 = { 1,2,3 };
	std::vector<int> v2 = std::move(v1);
	/// <summary>
	/// v1 goes size = 0, all data moved to v2
	/// </summary>
}

void TestForward()
{
	TestMove();
	TestPerfectForwarding();
}
