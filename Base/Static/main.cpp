/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/15
 *
 * \brief static���demo
 */

#include <iostream>
#include "Test.h"

using namespace std;

extern int iStaticGlobal;

//����Ĭ�϶���extern��,�˴���������ʹ��,�Ӳ���extern������,��������,�����extern
void func();

void FuncStatic();

//�����ռ��ڱ���������Ҫ�������ռ��ڰ���
namespace TestLinkage
{
	extern int iStaticNameSpace;
}

void Func()
{
	//��̬�ֲ�����,��������������ͷ�
	static int iStatic = 0;
	cout << "iStatic: " << iStatic++ << endl;
}

int main()
{
	//static�������ڲ�����,�ⲿ�ļ��޷�����
	//cout << TestLinkage::iStaticNameSpace;
	//cout << iStaticGlobal;

	//��̬����,�ⲿ�ļ��޷�ʹ��
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