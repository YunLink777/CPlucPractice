/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \brief Reference Demo
 */
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <list>
using namespace std;

//-------------------------------------------
//多态
class A
{
public:
	A() { cout << "Class A constructing..." << endl; }
	~A() { cout << "Class A destructing..." << endl; }
	//使用virtual关键字指定成员函数是虚函数
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

//Perfect forwarding完美转发
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

//通过模板函数调用成员函数，T是通过std::ref的方式传入的，必须通过get()方法获得对象的引用后再调用成员函数
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
	refA.print();	//print是虚函数，refA指向C对象，此处调用是C的print

	//-------------------------------------------
	//rvalue reference
	int i = 10;
	int& lr = i;
	int&& rr = 10;	//和左值引用一样，声明右值引用时也必须初始化
	rr = 100;	//右值引用可以修改右值

	Test test();
	cout << "Before copy" << endl;
	Test t = GetTest();
	cout << "Before move" << endl;
	Test&& rt = GetTest();	//GetTest返回的临时变量就是右值，直接赋值给rt，此处没有移动构造函数
	cout << "Before move1" << endl;
	Test rt1(GetTest());	//移动构造函数
	Test rt2(std::move(t));	//使用 std::move 将左值转换为右值，因此可以调用移动构造函数
	Test rt3 = std::move(t);

	//完美转发，当进行类型推导时，实参是右值引用，形参T&&就是右值引用，实参是左值引用，T&&就是左值引用
	int aa = 10;
	int&& bb = std::move(aa);
	forwardValue(10);	//r
	forwardValue(aa);	//l
	forwardValue(bb);	//l		bb是右值引用，但是b自身是左值
	forwardValue(std::move(aa));	//r
	//下面是rValue, forward其实就是static_cast<T&&>(aa),T是int，结果就是int&&,右值引用
	//如果是在模板内调用std::forward<T>(aa), 由于T&&是万能引用，T的类型和aa是一致的，所以可以完美转发
	forwardValue(std::forward<int>(aa));	
	//下面编译失败，std::forward的源码有规则，如果实参是右值引用的话，T不能是左值引用
	//forwardValue(std::forward<int&>(std::move(aa)));

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

	cout << "Contents of the list: ";
	for (auto& i : l)
	{
		cout << i;
	}
	cout << endl;

	getchar();
	return 0;
}