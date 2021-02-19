/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \brief 面向对象构造、析构、initializer_list等demo
 */

#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

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

class Test1
{
public:
	Test1(int x) {}
};
class Test
{
public:
	//初始化列表的顺序并不是真实的构造顺序，真实的顺序是变量声明的顺序
	Test(int i, float f, bool b, int gInt, int rInt)
		: m_i(i)
		, m_f(f)
		, m_b(b)
		, m_gInt(gInt)
		, m_rInt(rInt)
		, test1(i)
	{
		cout << "Test(int i, float f, bool b) called." << endl;
	}

	//委托构造函数
	Test() : Test(0, 0.0, false, 0, 0)
	{
		cout << "Test() called." << endl;
	}

	Test(const Test& t)
		: test1(t.test1)
		, m_gInt(0)
		, m_rInt(t.m_rInt)
	{
		cout << "Test copy constructor called\n";
	}

	void fun();

	//成员变量里有const和引用类型时，必须通过初始化列表对成员变量显示初始化，因为这两种类型声明时就要初始化，不能隐式初始化
	//另外成员变量里存在没有默认构造函数的变量时，也必须通过初始化列表进行显示初始化
	int m_i;
	float m_f;
	bool m_b;
	const int m_gInt;
	int& m_rInt;
	Test1 test1;
};

//委托构造函数，也可以在类定义外的构造函数定义中指明委托构造函数
//Test::Test():Test(0, 0.0, false){}

void Test::fun()
{

}

//***********************************************************//
//initializer_list
//initializer_list可用于实现同一类型但个数未知的参数接收,使用可变参数列表也可以实现
template <class T>
struct S {
	vector<T> v;
	//支持构造函数传入一个initializer_list参数
	S(initializer_list<T> l) : v(l)
	{
		cout << "constructed with a " << l.size() << "-elements lists" << endl;
	}
	void append(std::initializer_list<T> l)
	{
		v.insert(v.end(), l.begin(), l.end());
	}

	pair<const T*, size_t> c_arr() const
	{
		return { &v[0], v.size() };
	}

};

//接收同一类型个数未知参数的函数
template <typename T>
void templated_fn(T arg) {
	for (auto a : arg)
		cout << a << " ";
	cout << endl;
}

int main()
{
	//隐式转换,加了explicit关键字,无法隐式转换
	//Integer Int = 10;
	Integer Int(19);

	//析构函数不加virtual,会导致由基类指针指向的派生类对象析构时,无法调用派生类的析构函数,可能导致派生类中的资源得不到释放
	//调用了派生类的析构函数,基类的析构函数也会在之后被自动调用
	//先析构派生类,再析构基类
	Derive* derive = new Derive(1.1);
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
	//如果所有参数类型一致,其实是构造了一个initializer_list对象,如果test类有一个接收initializer_list参数的构造函数,就会调用这个构造函数
	Test test{ 0, 1.1f, false, 0, 0 };
	Test test2 = { 0, 1.1f, false, 0, 0 };
	//可以通过大括号初始化向量等数据结构
	vector<Test> vectors = { {0, 1.1, false, 0, 0}, {1, 2.1, true, 0, 0}, {4, 3.1, true, 0, 0} };
	cout << vectors.size() << endl;

	cout << "********************************\n";
	//initialzer_list
	//此处只创建3个Test对象,test这个对象会被拷贝一个副本到list_t里,拷贝构造函数会被调用
	initializer_list<Test> list_t = { test, {0, 1.1, false, 0, 0}, {1, 2.1, true, 0, 0}, {4, 3.1, true, 0, 0} };

	//一个initializer_list对象赋值给另一个initializer_list对象,元素不会拷贝,只是引用
	initializer_list<Test> list_copy = list_t;

	cout << "********************************\n";

	S<int> s = { 1, 2, 3, 4, 5 }; //自动创建一个initializer_list对象,并且拷贝大括号里的数据 

	s.append({ 6, 7 , 8 });         //list-initialization in function call

	cout << "The vector size is now " << s.c_arr().second << " ints:" << endl;

	for (auto n : s.v)
		cout << ' ' << n;
	cout << endl;

	cout << "range-for over brace-init-list: " << endl;

	for (auto x : { -1, -2, 03 })   //// for中有大括号,也自动创建一个initializer_list对象
		cout << x << " ";
	cout << endl;

	//此处auto类型推导 推导出的类型推断为一个initializer_list类型
	//如果{}中数据类型不一致,则编译错误
	//auto a2 = { 1, 1.1 };
	auto al = { 10, 11, 12 };  

	cout << "The list bound to auto has size() = " << al.size() << endl;

	//compiler error! "{1, 2, 3}" 模板推导无法推导{1,2,3}这种大括号括起来的类型,这点和auto类型推导不一样
	//templated_fn({1, 2, 3});  
	//可以显示传入一个initializer_list对象参数
	templated_fn<initializer_list<int> >({ 7, 8, 9 }); //ok
	templated_fn<vector<int> >({ 3, 5, 7 });           //also ok

	system("pause");
	return 0;
}