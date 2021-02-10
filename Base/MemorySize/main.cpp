/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/9
 *
 * \brief 内存占用大小demo
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

class DeriveD : public virtual Base
{
public:

	virtual void PrintName()
	{
		cout << "DeriveD" << endl;
	}
};

class DeriveE : public virtual Base
{
public:

	int m_bValue;

	virtual void PrintName()
	{
		cout << "DeriveE" << endl;
	}

	virtual void run() {};
};

class DeriveF : public DeriveD, public DeriveE
{
public:
	int m_iValue;
	virtual void PrintName()
	{
		cout << "DeriveF" << endl;
	}
	virtual void RunF() {};
};

int main()
{
	//在C++里，NULL就是0，nullptr是空指针
	printfun(NULL);
	printfun(nullptr);
	cout << "***************************" << endl;

	//64为系统下各类型变量的大小
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

	//64位系统下指针大小是8字节,32位下是4字节
	int* pi = new int(0);
	PrintTypeSize(pi);
	cout << "***************************" << endl;

	//类对象和继承的内存占用大小
	Base base;
	DeriveA A;
	DeriveB B;
	DeriveC C;
	BaseA* base1 = new BaseA;

	//16字节, m_iValue4字节,虚函数表指针8字节,对齐后就是16字节,内存结构:Base虚函数表-Base成员
	PrintTypeSize(base);	
	//16字节,Base的m_iValue 4字节,虚函数表指针8字节,对齐后就是16字节,内存结构:A和Base虚函数表表-Base成员
	PrintTypeSize(A);	
	//24字节,再加上自己的m_bValue4字节,对齐就是24字节,内存结构:B和Base虚函数表-Base成员-B成员
	PrintTypeSize(B);	
	//40字节,就是A和B的大小之和 Base对象有两份,虚函数表指针也有两个,A一个B一个,还有一个m_bValue
	//内存结构:C和A虚函数表-Base成员-B虚函数表-Base成员-B成员
	PrintTypeSize(C);	
	//没有成员变量,但是编译器会插入一个char,1个字节
	PrintTypeSize(*base1);	

	cout << "***************************" << endl;

	DeriveD D;
	DeriveE E;
	DeriveF F;

	//24字节,D没有新的虚函数,虚继承Base后,内存结构依次为:D虚基类表-Base的虚函数表-Base成员
	PrintTypeSize(D);	
	//40字节,E有新的虚函数,因此有自己的虚函数表
	//内存结构依次为:E虚函数表-E虚基类表-E成员-Base虚函数表-Base成员
	PrintTypeSize(E);	
	//56字节,D没有自己的虚函数表，因此只有E和F有虚函数表，如果D也有自己的虚函数表,那此处和普通多重继承一样,字节将变为64个字节
	//内存结构依次为F虚函数表-D虚基类表-E虚基类表-E成员-F成员-Base虚函数表-Base成员
	PrintTypeSize(F);	
	

	getchar();
	return 0;
}