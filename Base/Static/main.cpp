/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/15
 *
 * \brief static���demo
 */

#include <iostream>
#include <thread>
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
	//��̬�ֲ�����(local static),��������������ͷ�
	static int iStatic = 0;
	cout << "iStatic: " << iStatic++ << endl;
}

void CreateTest(const std::string& thread_name)
{
	//��̬�ֲ�����(local static)��������������һ�ε���ǰ�������ڣ�ֻ�е�һ�ε���ʱ�ſ�ʼ��ʼ��
	//�Ǿ�̬�ֲ�����(ȫ��  ��Ա  �����ռ��ڵ�)��main����ִ��ǰ���Ѿ�����˳�ʼ��
	//c++11��ʼ����̬�ֲ�����(local static)��ʼ�������У��������̶߳�ִ�д˶δ��룬�ʼ���̳߳�ʼ������ǰ�������̶߳���ȴ��ʼ���̳߳�ʼ������
	cout << thread_name << " thread start" << endl;
	static Test test;
	cout << thread_name << " thread end" << endl;
}

//�Ǿ�̬�ֲ�����(ȫ��  ��Ա  �����ռ��ڵ�)��main����ִ��ǰ���Ѿ�����˳�ʼ��
static Test staticTest;

int main()
{
	cout << "main start" << endl;
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

	std::thread A (CreateTest, "A"), B(CreateTest, "B");

	getchar();
	return 0;
}