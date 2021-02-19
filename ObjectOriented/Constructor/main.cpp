/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \brief ��������졢������demo
 */

#include <iostream>
#include <string>
#include <vector>

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

	//ί�й��캯��
	Test() : Test(0, 0.0, false) 
	{
		cout << "Test() called." << endl;
	}
	void fun();

	int m_i;
	float m_f;
	bool m_b;
};

//ί�й��캯����Ҳ�������ඨ����Ĺ��캯��������ָ��ί�й��캯��
//Test::Test():Test(0, 0.0, false){}

void Test::fun()
{

}

int main()
{
	//��ʽת��,����explicit�ؼ���,�޷���ʽת��
	//Integer Int = 10;
	Integer Int(19);

	//������������virtual,�ᵼ���ɻ���ָ��ָ����������������ʱ,�޷��������������������,���ܵ����������е���Դ�ò����ͷ�
	//���������������������,�������������Ҳ����֮���Զ�����
	//������������,����������
	Derive *derive = new Derive(1.1);
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
	Test test{ 0, 1.1f, false };
	//����ͨ�������ų�ʼ�����������ݽṹ
	vector<Test> vectors = { {0, 1.1, false}, {1, 2.1, true}, {4, 3.1, true} };
	cout << vectors.size() << endl;
	system("pause");
	return 0;
}