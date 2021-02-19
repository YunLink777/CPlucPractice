/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \brief 面向对象构造、析构等demo
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Integer
{
public:
	//单个参数的构造函数，如果不加explicit关键字，是可以隐式转换的
	explicit Integer(int num) : m_num(num) {};
	int Get() { return m_num; }
	void Set(int num) { m_num = num; }
private:
	int m_num;
};

class Base
{
public:
	Base() = default;
	Base(int num) :m_pInt(new int(num))
	{
		cout << "Base " << num << " constructing." << endl;
	}

	//虚析构函数,可以避免基类指针指向派生类对象时,通过基类指针调用析构函数无法调用派生类析构函数的问题
	virtual ~Base() 
	{
		cout << "Base destructor finished." << endl;
		if (m_pInt != nullptr)
		{
			cout << "Num: " << *m_pInt << endl;
			delete m_pInt;
		}
	}

private:
	int* m_pInt = nullptr;
};

class Derive : public Base
{
public:
	Derive() = default;
	Derive(float num) :m_pFloat(new float(num)) {}
	~Derive()
	{
		if (m_pFloat != nullptr)
		{
			delete m_pFloat;
		}
		cout << "Derive destructor finished." << endl;
	}

private:
	float* m_pFloat = nullptr;
};

//构造函数和析构函数调用顺序
class A {
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
};

class F
{
public:
	F() { cout << "F()" << endl; }
	~F() { cout << "~F()" << endl; }
};

class B {
public:
	B(int b) { cout << "B(" << b << ")" << endl; }
	~B() { cout << "~B()" << endl; }

	F f;
};

class C {
public:
	C(int c) { cout << "C(" << c << ")" << endl; }
	~C() { cout << "~C()" << endl; }
};

class D {
public:
	D() { cout << "D()" << endl; }
	~D() { cout << "~D()" << endl; }
};

class E : public B, public A {
public:
	D d;
	C c;
	E() : c(3), B(5) { cout << "E()" << endl; }
	~E() { cout << "~E()" << endl; }
};

//********************************

class Test
{
public:
	Test(int i, float f, bool b)
		: m_i(i)
		, m_f(f)
		, m_b(b)
	{
		cout << "Test(int i, float f, bool b) called." << endl;
	}

	//委托构造函数
	Test() : Test(0, 0.0, false) 
	{
		cout << "Test() called." << endl;
	}
	void fun();

	int m_i;
	float m_f;
	bool m_b;
};

//委托构造函数，也可以在类定义外的构造函数定义中指明委托构造函数
//Test::Test():Test(0, 0.0, false){}

void Test::fun()
{

}

int main()
{
	//隐式转换,加了explicit关键字,无法隐式转换
	//Integer Int = 10;
	Integer Int(19);

	//析构函数不加virtual,会导致由基类指针指向的派生类对象析构时,无法调用派生类的析构函数,可能导致派生类中的资源得不到释放
	//调用了派生类的析构函数,基类的析构函数也会在之后被自动调用
	//先析构派生类,再析构基类
	Derive *derive = new Derive(1.1);
	Base* pBase = derive;
	delete pBase;
	//delete derive;

	cout << "*************************************\n";
	//栈中创建对象,析构的顺序和创建的顺序相反,因为栈是先进后出
	{
		Base b1(1);
		Base b2(2);
		Base b3(3);
		cout << "*************************************\n";
	}

	cout << "*************************************\n";
	//构造函数和析构函数调用顺序
	//先调用虚基类构造函数,再按照继承顺序从左到右调用构造基类构造函数
	//再按照成员变量在类定义中的声明顺序调用成员变量构造函数
	//最后执行本身构造函数的代码
	//和初始化列表中的顺序可能是不一致的
	//析构函数的调用顺序和构造函数顺序相反,先构造的后析构
	//构造的顺序也就是类对象内存结构中各内存块的顺序(除了虚基类内存块顺序固定在最后这点不一样)
	{
		E e;
		cout << "*************************************\n";
	}

	cout << "*************************************\n";

	//委托构造函数
	{
		Test t;
	}

	cout << "*************************************\n";
	//可以通过大括号初始化对象，大括号内变量的顺序需要在某个该类构造函数中一致
	Test test{ 0, 1.1f, false };
	//可以通过大括号初始化向量等数据结构
	vector<Test> vectors = { {0, 1.1, false}, {1, 2.1, true}, {4, 3.1, true} };
	cout << vectors.size() << endl;
	system("pause");
	return 0;
}