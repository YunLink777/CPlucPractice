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
//��̬
class A
{
public:
	A() { cout << "Class A constructing..." << endl; }
	~A() { cout << "Class A destructing..." << endl; }
	//ʹ��virtual�ؼ���ָ����Ա�������麯��
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

//Perfect forwarding����ת��
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

//ͨ��ģ�庯�����ó�Ա������T��ͨ��std::ref�ķ�ʽ����ģ�����ͨ��get()������ö�������ú��ٵ��ó�Ա����
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
	refA.print();	//print���麯����refAָ��C���󣬴˴�������C��print

	//-------------------------------------------
	//rvalue reference
	int i = 10;
	int& lr = i;
	int&& rr = 10;	//����ֵ����һ����������ֵ����ʱҲ�����ʼ��
	rr = 100;	//��ֵ���ÿ����޸���ֵ

	Test test();
	cout << "Before copy" << endl;
	Test t = GetTest();
	cout << "Before move" << endl;
	Test&& rt = GetTest();	//GetTest���ص���ʱ����������ֵ��ֱ�Ӹ�ֵ��rt���˴�û���ƶ����캯��
	cout << "Before move1" << endl;
	Test rt1(GetTest());	//�ƶ����캯��
	Test rt2(std::move(t));	//ʹ�� std::move ����ֵת��Ϊ��ֵ����˿��Ե����ƶ����캯��
	Test rt3 = std::move(t);

	//����ת���������������Ƶ�ʱ��ʵ������ֵ���ã��β�T&&������ֵ���ã�ʵ������ֵ���ã�T&&������ֵ����
	int aa = 10;
	int&& bb = std::move(aa);
	forwardValue(10);	//r
	forwardValue(aa);	//l
	forwardValue(bb);	//l		bb����ֵ���ã�����b��������ֵ
	forwardValue(std::move(aa));	//r
	//������rValue, forward��ʵ����static_cast<T&&>(aa),T��int���������int&&,��ֵ����
	//�������ģ���ڵ���std::forward<T>(aa), ����T&&���������ã�T�����ͺ�aa��һ�µģ����Կ�������ת��
	forwardValue(std::forward<int>(aa));	
	//�������ʧ�ܣ�std::forward��Դ���й������ʵ������ֵ���õĻ���T��������ֵ����
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