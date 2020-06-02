
#include "CountData.hpp"
#include <memory>
#include <vector>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;
struct C
{
	Counter<C> count_; //引入私有成员变量
};

class A
{

	Counter<A> count_; //引入私有成员变量
};

A* CreateA(void)
{
	return new A;
}

void f(void)
{
	auto p = new A;
}

class MyClass
{
public:
	MyClass();
	~MyClass();
private:
	Counter<MyClass> count_; //引入私有成员变量
};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

class B
{
public:
	B();
	~B();

private:
	Counter<B> count_; //引入私有成员变量
};

B::B()
{
}

B::~B()
{
}



int main() 
{

	auto pa = new A;//这里泄漏1次
	auto aa = new A[5];//这里泄漏5个
	auto p2 = CreateA();
	delete p2;
	f();//这里泄漏了1次
	new MyClass;//这里泄漏了一次
	new B;//这里泄漏了一次
	auto listA = std::vector<std::shared_ptr<A>>(5, std::make_shared<A>());//这里没有泄露
	for (int i = 0; i < 3; ++i)
	{
		listA.push_back(std::make_shared<A>());//这里没有泄漏
	}
	auto pc = new C;
	delete pc;	 

	return 0;
}
 


 