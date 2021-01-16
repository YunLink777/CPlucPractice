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

int main(int argc, char* argv[])
{
	A a;
	B b;
	C c;
	A& refA = c;
	refA.print();	//refA ref to a C object, and print is virtual, so this print is c's print
	getchar();
	return 0;
}