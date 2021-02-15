#include "Test.h"
#include <windows.h>

//静态全局变量,内部链接只在本文件内可见
static int iStaticGlobal = 16;

//如果加了命名空间作用域,其他文件里只要声明了命名空间里的变量,也可以通过命名空间调用的方式调用变量
namespace TestLinkage
{
	//static静态链接,内部链接
	static int iStaticNameSpace = 10;
}

//静态函数,只在本文件内可用
static void FuncStatic()
{
	std::cout << "FuncStatic in Test.cpp" << std::endl;
}

void func()
{
	std::cout << "func in Test.cpp ";
	FuncStatic();
}

Test::Test()
{
	//增加延时，使构造过程更明显
	Sleep(4000);
	std::cout << "Test constructing finished." << std::endl;
}

//静态成员变量初始化
int Test::m_iStatic = 10;
//静态成员函数初始化
void Test::FuncStaticB()
{
	m_iStatic++;
	//m_iNonStatic++;
	std::cout << "Static func B in Test class" << std::endl;
}