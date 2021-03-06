/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/15
 *
 * \brief static相关demo
 */

#include <iostream>
#include <thread>
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
	//静态局部变量(local static),不随作用域结束释放
	static int iStatic = 0;
	cout << "iStatic: " << iStatic++ << endl;
}

void CreateTest(const std::string& thread_name)
{
	//静态局部变量(local static)在所属函数被第一次调用前并不存在，只有第一次调用时才开始初始化
	//非静态局部变量(全局  成员  命名空间内等)在main函数执行前就已经完成了初始化
	//c++11开始，静态局部变量(local static)初始化过程中，如果多个线程都执行此段代码，最开始的线程初始化结束前，其他线程都会等待最开始的线程初始化结束
	cout << thread_name << " thread start" << endl;
	static Test test;
	cout << thread_name << " thread end" << endl;
}

//非静态局部变量(全局  成员  命名空间内等)在main函数执行前就已经完成了初始化
static Test staticTest;

int main()
{
	cout << "main start" << endl;
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

	std::thread A (CreateTest, "A"), B(CreateTest, "B");

	getchar();
	return 0;
}