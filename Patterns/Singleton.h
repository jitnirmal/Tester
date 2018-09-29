#pragma once
#include <iostream>
//https://www.boost.org/doc/libs/1_54_0/doc/html/atomic/usage_examples.html
template <class T>
class SingletonBase
{
protected:
	SingletonBase() {}
public:
	SingletonBase(SingletonBase const &) = delete;
	SingletonBase& operator=(SingletonBase const&) = delete;
	static T& instance()
	{
		static T single;
		return single;
	}
};

class Single : public SingletonBase<Single>
{
	Single() {}
	friend class SingletonBase<Single>;
public:
	void demo() { std::cout << "demo" << std::endl; }
};


class IVisitor
{
public:
	IVisitor();
	virtual ~IVisitor();

	virtual void visit(IVisitable&) = 0;

};

class IVisitable
{
public:
	IVisitable();
	virtual ~IVisitable();

	void onVisitBy(IVisitor& visitor);
};

inline void IVisitable::onVisitBy(IVisitor& visitor)
{
	visitor.visit(*this);
}