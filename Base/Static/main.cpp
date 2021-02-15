/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/15
 *
 * \brief static相关demo
 */

#include <iostream>
#include "Test.h"

using namespace std;

extern int iStaticGlobal;

//函数默认都是extern的,此处声明即可使用,加不加extern都可以,变量不行,必须加extern
void func();

void FuncStatic();

//命名空间内变量的声明要在命名空间内包含
namespace TestLinkage
{
	extern int iStaticNameSpace;
}

void Func()
{
	//静态局部变量,不随作用域结束释放
	static int iStatic = 0;
	cout << "iStatic: " << iStatic++ << endl;
}

int main()
{
	//static变量是内部链接,外部文件无法访问
	//cout << TestLinkage::iStaticNameSpace;
	//cout << iStaticGlobal;

	//静态函数,外部文件无法使用
	//FuncStatic();
	func();

	Func();
	Func();

	cout << "Test::m_iStatic: " << Test::m_iStatic << endl;
	Test::FuncStaticA();
	Test::FuncStaticB();
	Test a, b;
	cout << "Test a.m_iStatic: " << a.m_iStatic << endl;
	cout << "Test b.m_iStatic: " << b.m_iStatic << endl;
	getchar();
	return 0;
}