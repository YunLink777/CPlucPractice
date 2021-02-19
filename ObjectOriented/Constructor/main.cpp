/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \brief ��������졢������initializer_list��demo
 */

#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

using namespace std;

class Integer
{
public:
	//���������Ĺ��캯�����������explicit�ؼ��֣��ǿ�����ʽת����
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

	//����������,���Ա������ָ��ָ�����������ʱ,ͨ������ָ��������������޷�������������������������
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

//���캯����������������˳��
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
	//��ʼ���б��˳�򲢲�����ʵ�Ĺ���˳����ʵ��˳���Ǳ���������˳��
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

	//ί�й��캯��
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

	//��Ա��������const����������ʱ������ͨ����ʼ���б�Գ�Ա������ʾ��ʼ������Ϊ��������������ʱ��Ҫ��ʼ����������ʽ��ʼ��
	//�����Ա���������û��Ĭ�Ϲ��캯���ı���ʱ��Ҳ����ͨ����ʼ���б������ʾ��ʼ��
	int m_i;
	float m_f;
	bool m_b;
	const int m_gInt;
	int& m_rInt;
	Test1 test1;
};

//ί�й��캯����Ҳ�������ඨ����Ĺ��캯��������ָ��ί�й��캯��
//Test::Test():Test(0, 0.0, false){}

void Test::fun()
{

}

//***********************************************************//
//initializer_list
//initializer_list������ʵ��ͬһ���͵�����δ֪�Ĳ�������,ʹ�ÿɱ�����б�Ҳ����ʵ��
template <class T>
struct S {
	vector<T> v;
	//֧�ֹ��캯������һ��initializer_list����
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

//����ͬһ���͸���δ֪�����ĺ���
template <typename T>
void templated_fn(T arg) {
	for (auto a : arg)
		cout << a << " ";
	cout << endl;
}

int main()
{
	//��ʽת��,����explicit�ؼ���,�޷���ʽת��
	//Integer Int = 10;
	Integer Int(19);

	//������������virtual,�ᵼ���ɻ���ָ��ָ����������������ʱ,�޷��������������������,���ܵ����������е���Դ�ò����ͷ�
	//���������������������,�������������Ҳ����֮���Զ�����
	//������������,����������
	Derive* derive = new Derive(1.1);
	Base* pBase = derive;
	delete pBase;
	//delete derive;

	cout << "*************************************\n";
	//ջ�д�������,������˳��ʹ�����˳���෴,��Ϊջ���Ƚ����
	{
		Base b1(1);
		Base b2(2);
		Base b3(3);
		cout << "*************************************\n";
	}

	cout << "*************************************\n";
	//���캯����������������˳��
	//�ȵ�������๹�캯��,�ٰ��ռ̳�˳������ҵ��ù�����๹�캯��
	//�ٰ��ճ�Ա�������ඨ���е�����˳����ó�Ա�������캯��
	//���ִ�б����캯���Ĵ���
	//�ͳ�ʼ���б��е�˳������ǲ�һ�µ�
	//���������ĵ���˳��͹��캯��˳���෴,�ȹ���ĺ�����
	//�����˳��Ҳ����������ڴ�ṹ�и��ڴ���˳��(����������ڴ��˳��̶��������㲻һ��)
	{
		E e;
		cout << "*************************************\n";
	}

	cout << "*************************************\n";

	//ί�й��캯��
	{
		Test t;
	}

	cout << "*************************************\n";
	//����ͨ�������ų�ʼ�����󣬴������ڱ�����˳����Ҫ��ĳ�����๹�캯����һ��
	//������в�������һ��,��ʵ�ǹ�����һ��initializer_list����,���test����һ������initializer_list�����Ĺ��캯��,�ͻ����������캯��
	Test test{ 0, 1.1f, false, 0, 0 };
	Test test2 = { 0, 1.1f, false, 0, 0 };
	//����ͨ�������ų�ʼ�����������ݽṹ
	vector<Test> vectors = { {0, 1.1, false, 0, 0}, {1, 2.1, true, 0, 0}, {4, 3.1, true, 0, 0} };
	cout << vectors.size() << endl;

	cout << "********************************\n";
	//initialzer_list
	//�˴�ֻ����3��Test����,test�������ᱻ����һ��������list_t��,�������캯���ᱻ����
	initializer_list<Test> list_t = { test, {0, 1.1, false, 0, 0}, {1, 2.1, true, 0, 0}, {4, 3.1, true, 0, 0} };

	//һ��initializer_list����ֵ����һ��initializer_list����,Ԫ�ز��´��,ֻ������
	initializer_list<Test> list_copy = list_t;

	cout << "********************************\n";

	S<int> s = { 1, 2, 3, 4, 5 }; //�Զ�����һ��initializer_list����,���ҿ���������������� 

	s.append({ 6, 7 , 8 });         //list-initialization in function call

	cout << "The vector size is now " << s.c_arr().second << " ints:" << endl;

	for (auto n : s.v)
		cout << ' ' << n;
	cout << endl;

	cout << "range-for over brace-init-list: " << endl;

	for (auto x : { -1, -2, 03 })   //// for���д�����,Ҳ�Զ�����һ��initializer_list����
		cout << x << " ";
	cout << endl;

	//�˴�auto�����Ƶ� �Ƶ����������ƶ�Ϊһ��initializer_list����
	//���{}���������Ͳ�һ��,��������
	//auto a2 = { 1, 1.1 };
	auto al = { 10, 11, 12 };  

	cout << "The list bound to auto has size() = " << al.size() << endl;

	//compiler error! "{1, 2, 3}" ģ���Ƶ��޷��Ƶ�{1,2,3}���ִ�����������������,����auto�����Ƶ���һ��
	//templated_fn({1, 2, 3});  
	//������ʾ����һ��initializer_list�������
	templated_fn<initializer_list<int> >({ 7, 8, 9 }); //ok
	templated_fn<vector<int> >({ 3, 5, 7 });           //also ok

	system("pause");
	return 0;
}