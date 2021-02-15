/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/9
 *
 * \brief 存储和链接相关demo
 */

#include <iostream>
#include <thread>
#include <mutex>
#include "Test.h"

using namespace std;

//声明外部int变量,已在其他文件里定义,声明后可直接使用
extern int iExtern;
extern int iGlobal;
extern int iInternal;
extern const int iConst;
extern const int iConstExtern;
extern int iStaticGlobal;

//函数默认都是extern的,此处声明即可使用,加不加extern都可以,变量不行,必须加extern
void func();

//命名空间内变量的声明要在命名空间内包含
namespace TestLinkage
{
	extern int iExternNameSpace;
	extern int iNameSpace;
	extern int iStaticNameSpace;
}

//thread_local变量,存储期是线程,每个线程都有一个该变量
thread_local unsigned int rage = 1;
std::mutex cout_mutex;

void increase_rage(const std::string& thread_name)
{
	++rage; // 锁外修改是没问题的;这是一个thread-local 变量
	std::lock_guard<std::mutex> lock(cout_mutex);
	std::cout << "Rage counter for " << thread_name << ": " << rage << '\n';
}

int main()
{
	cout << "iExtern define in Test.cpp : " << iExtern << endl;
	iExtern++;
	cout << "iExtern define in Test.cpp : " << iExtern << endl;
	cout << "iGlobal define in Test.cpp : " << iGlobal << endl;

	cout << "iNameSpace define in Test.cpp : " << TestLinkage::iNameSpace << endl;
	cout << "iExternNameSpace define in Test.cpp : " << TestLinkage::iExternNameSpace << endl;

	//const变量默认是static的
	//cout << iConst;
	cout << "iConstExtern define in Test.cpp : " << iConstExtern << endl;

	//定义在头文件内的const变量,包含头文件相当于在本文件内再次定义了一遍,存在两个const变量
	//由于const是默认static和不变的常量,所以这么用也没问题
	cout << "iConstInH define in Test.h : " << iConstInH << endl;

	//static变量是内部链接,外部文件无法访问
	//cout << TestLinkage::iStaticNameSpace;
	//cout << iStaticGlobal;

	//无法使用块作用域内定义的变量
	//cout << iInternal;

	func();

	std::thread a(increase_rage, "a"), b(increase_rage, "b");

	{
		std::lock_guard<std::mutex> lock(cout_mutex);
		std::cout << "Rage counter for main: " << rage << '\n';
	}

	a.join();
	b.join();

	getchar();
	return 0;
}