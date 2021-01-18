/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \description: Reference Demo
 */
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <list>
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

//-----------------------------------------------
//std::reference_wrapper
template <typename T>
void testPrint(T t) 
{
	++t;
}

//if you call a member function in template function, and you pass the T as std::ref way, you must call the member function after get() to get the ref of the object
template <typename T>
void testPrint1(T t)
{
	t.get().print();
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
	Test rt3 = std::move(t);

	//Perfect forwarding, when processing type inference, formal parameter T&& will be rvalue reference when actual parameter is rvalue, 
	//T&& will be lvalue reference when actual parameter is lvalue
	int aa = 10;
	forwardValue(10);
	forwardValue(aa);

	//-----------------------------------------------
	//std::reference_wrapper
	//wrap a value to a reference object
	int x = 10;
	testPrint(x);	//pass as value
	cout << "x: " << x << endl;

	//two kinds of std::reference_wrapper useage
	auto y = std::ref(x);
	std::reference_wrapper<decltype(x)> z(x);

	testPrint(std::ref(x));	//pass as ref through std::ref
	cout << "x: " << x << endl;
	testPrint(y);
	cout << "x: " << x << endl;
	testPrint(z);
	cout << "x: " << x << endl;

	//call member function with ref
	testPrint1(std::ref(a));

	//------------------------------------------
	//std::ref in std container
	//the std container only support value not ref, but you can pass ref with std::ref
	std::list<int> l(10);
	std::iota(l.begin(), l.end(), -4);
	//create a vector with elements are ref of list l
	std::vector<std::reference_wrapper<int> > v(l.begin(), l.end());

	// can't use shuffle on a list (requires random access), but can use it on a vector
	std::shuffle(v.begin(), v.end(), std::mt19937{ std::random_device{}() });

	cout << "Contents of the list: ";
	for (auto& i : l)
	{
		cout << i;
	}
	cout << endl;

	cout << "Contents of the vector: ";
	for (auto& i : v)
	{
		cout << i;
	}
	cout << endl;

	cout << "Doubling the values in the initial list...\n";
	for (int& i : l)
	{
		i *= 2;
	}

	cout << "Contents of the vector: ";
	for (auto& i : v)
	{
		cout << i;
	}
	cout << endl;

	getchar();
	return 0;
}