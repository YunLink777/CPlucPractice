/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/9
 *
 * \brief �ڴ�ռ�ô�Сdemo
 */

#include <iostream>

using namespace std;

void printfun(int i)
{
	cout << "print int" << endl;
}

void printfun(void* v)
{
	cout << "print pointer" << endl;
}

template<typename Value>
void PrintTypeSize(Value v)
{
	cout << typeid(v).name() << " size: " << sizeof(v) << " Bytes." << endl;
}

class Base
{
public:
	int m_iValue = 0;
	
	virtual void PrintName()
	{
		cout << "Base" << endl;
	}
};

class DeriveA : public Base
{
public:

	virtual void PrintName()
	{
		cout << "DeriveA" << endl;
	}
};

class DeriveB : public Base
{
public:

	int m_bValue;

	virtual void PrintName()
	{
		cout << "DeriveB" << endl;
	}
};

class BaseA
{

};

class DeriveC : public DeriveA, public DeriveB
{
public:
	virtual void PrintName()
	{
		cout << "DeriveC" << endl;
	}
};

int main()
{
	//��C++�NULL����0��nullptr�ǿ�ָ��
	printfun(NULL);
	printfun(nullptr);
	cout << "***************************" << endl;

	//64Ϊϵͳ�¸����ͱ����Ĵ�С
	char c = '0';
	PrintTypeSize(c);
	unsigned char uc = '0';
	PrintTypeSize(uc);
	bool b = true;
	PrintTypeSize(b);
	signed char sc = '0';
	PrintTypeSize(sc);
	__int8 i8 = 0;
	PrintTypeSize(i8);
	char8_t c8 = '0';
	PrintTypeSize(c8);
	cout << "***************************" << endl;

	short si = 0;
	PrintTypeSize(si);
	unsigned short usi = 0;
	PrintTypeSize(usi);
	char16_t c16 = '0';
	PrintTypeSize(c16);
	__int16 i16 = 0;
	PrintTypeSize(i16);
	cout << "***************************" << endl;

	int i = 0;
	PrintTypeSize(i);
	__int32 i32 = 0;
	PrintTypeSize(i32);
	long il = 0;
	PrintTypeSize(il);
	char32_t c32 = '0';
	PrintTypeSize(c32);
	float f = 0.0;
	PrintTypeSize(f);
	cout << "***************************" << endl;

	double d = 0.0;
	PrintTypeSize(d);
	long long ll = 0;
	PrintTypeSize(ll);
	__int64 i64 = 0;
	PrintTypeSize(i64);
	long double ld = 0.0;
	PrintTypeSize(ld);
	cout << "***************************" << endl;

	//64λϵͳ��ָ���С��8�ֽ�,32λ����4�ֽ�
	int* pi = new int(0);
	PrintTypeSize(pi);
	cout << "***************************" << endl;

	//�����ͼ̳е��ڴ�ռ�ô�С
	Base base;
	DeriveA A;
	DeriveB B;
	DeriveC C;
	BaseA* base1 = new BaseA;

	PrintTypeSize(base);	//16�ֽ�, m_iValue4�ֽ�,�麯����ָ��8�ֽ�,��������16�ֽ�
	PrintTypeSize(A);	//16�ֽ�,Base��m_iValue 4�ֽ�,�麯����ָ��8�ֽ�,��������16�ֽ�
	PrintTypeSize(B);	//24�ֽ�,�ټ����Լ���m_bValue4�ֽ�,�������24�ֽ�
	PrintTypeSize(C);	//40�ֽ�,����A��B�Ĵ�С֮��,Base����������
	PrintTypeSize(*base1);	//û�г�Ա����,���Ǳ����������һ��char,1���ֽ�
	

	getchar();
	return 0;
}