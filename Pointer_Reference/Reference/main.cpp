/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \description: Reference Demo
 */
#include <iostream>
using namespace std;

//-------------------------------------------
//polymorphic
class A
{
public:
	A() { cout << "Class A constructing..." << endl; }
	~A() { cout << "Class A destructing..." << endl; }
	//use keyword virtual to define this member function can be inherit by A's derived class, and it's polymorphic
	virtual void print()
	{
		cout << "Class A print." << endl;
	}
};

class B  : public A
{
public:
	B() { cout << "Class B constructing..." << endl; }
	~B() { cout << "Class B destructing..." << endl; }
	virtual void print()
	{
		cout << "Class B print." << endl;
	}
};

class C : public B
{
public:
	C() { cout << "Class C constructing..." << endl; }
	~C() { cout << "Class C destructing..." << endl; }
	virtual void print()
	{
		cout << "Class C print." << endl;
	}
};

//-------------------------------------------
//rvalue reference
class Test
{
public:
	Test() { cout << "Constructing..." << endl; }
	~Test() { cout << "Destructing..." << endl; }
	Test(const Test& test)
	{
		cout << "Copy constructing..." << endl;
	}
	Test(Test&& test)
	{
		cout << "Move constructing..." << endl;
	}
};

Test&& GetTest()
{
	return Test();
}

//Perfect forwarding
void processValue(int& a) { cout << "lvalue" << endl; }
void processValue(int&& a) { cout << "rvalue" << endl; }
template <typename T>
void forwardValue(T&& val)
{
	processValue(std::forward<T>(val)); 
}


int main(int argc, char* argv[])
{
	A a;
	B b;
	C c;
	A& refA = c;
	refA.print();	//refA ref to a C object, and print is virtual, so this print is c's print

	//-------------------------------------------
	//rvalue reference
	int i = 10;
	int& lr = i;
	int&& rr = 10;	//when rvalue reference is declared, it must be initialized by rvalue
	rr = 100;	//rvalue reference can change rvalue

	Test test();
	cout << "Before copy" << endl;
	Test t = GetTest();
	cout << "Before move" << endl;
	Test&& rt = GetTest();

	Test rt1(GetTest());	//move copy constructor
	Test rt2(std::move(t));	//use std::move to make a lvalue to a rvalue, so move copy constructor will be called

	//Perfect forwarding
	int aa = 10;
	forwardValue(10);
	forwardValue(aa);

	getchar();
	return 0;
}