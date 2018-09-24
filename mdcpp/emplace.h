#pragma once

#include <iostream>
using namespace std;
#include <map>

struct Obj {
	Obj() { puts("const"); }
	Obj(int i, double d) { puts("const args"); }
	Obj(const Obj&) { puts("copy const"); }
	Obj(Obj&&) { puts("move const"); }
	Obj& operator=(const Obj&) { puts("copy assg"); return *this; }
	Obj& operator=(Obj&&) { puts("move assg"); return *this; }
	~Obj() { puts("dest"); }
};

void TestVectorEmplace()
{
	vector<Obj> vo;
//	vo.push_back(Obj()); // const mov-const dest dest
//	vo.emplace_back(Obj()); // const mov-const dest dest
	vo.emplace_back(); // const dest
	/// <summary>
	/// this is best case where object can be constructed in place. :)
	/// empty argument....as Obj has 0 args.. otherwise pass the args
	/// </summary>
}

void TestMapEmplace()
{
	std::map<int,Obj> mo;
//	mo[1] = Obj(); // const mov-const dest dest
//	mo.emplace(2, Obj());// const mov-const dest dest
//	mo.emplace(std::pair<int, Obj>(3, {}));// const copy-const mov-const dest dest dest
//	mo.emplace(std::piecewise_construct,std::forward_as_tuple(4),std::forward_as_tuple(1,2.4f)); // const dest // but expensive due to tuple conversions
	mo.try_emplace(4,1,2.4f); // const dest
	/// <summary>
	/// this is best way to construct the objects in place
	/// </summary>
}

void TestEmplace()
{
//	TestVectorEmplace();
	TestMapEmplace();

}
