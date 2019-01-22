#pragma once
#include <iostream>
#include <mutex>
#include <atomic>
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


/// <summary>
/// implementation with call once
/// </summary>
class CallOnceSingleton{

  private:
	  static std::once_flag initInstanceFlag;
	  static CallOnceSingleton* instance;
	  CallOnceSingleton() = default;
	  ~CallOnceSingleton() = default;

  public:
	  CallOnceSingleton(const CallOnceSingleton&) = delete;
	  CallOnceSingleton& operator=(const CallOnceSingleton&) = delete;

	  static CallOnceSingleton* getInstance() {
		  std::call_once(initInstanceFlag, CallOnceSingleton::initSingleton);
		  return instance;
	  }

	  static void initSingleton() {
		  instance = new CallOnceSingleton();
	  }
};

class X {
public:
	static X * instance()
	{
		X * tmp = _instance.load(std::memory_order_consume);
		if (!tmp) {
			std::lock_guard<std::mutex> guard(_mutex);
			tmp = _instance.load(std::memory_order_consume);
			if (!tmp) {
				tmp = new X;
				_instance.store(tmp, std::memory_order_release);
			}
		}
		return tmp;
	}
private:
	static std::atomic<X*> _instance;
	static std::mutex _mutex;
};



CallOnceSingleton* CallOnceSingleton::instance = nullptr;
std::once_flag CallOnceSingleton::initInstanceFlag;

void testCallOnceSingleton() {

	std::cout << std::endl;

	std::cout << "MySingleton::getInstance(): " << CallOnceSingleton::getInstance() << std::endl;
	std::cout << "MySingleton::getInstance(): " << CallOnceSingleton::getInstance() << std::endl;

	std::cout << std::endl;

}



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