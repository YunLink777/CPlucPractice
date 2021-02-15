/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/9
 *
 * \brief �洢���������demo
 */

#include <iostream>
#include <thread>
#include <mutex>
#include "Test.h"

using namespace std;

//�����ⲿint����,���������ļ��ﶨ��,�������ֱ��ʹ��
extern int iExtern;
extern int iGlobal;
extern int iInternal;
extern const int iConst;
extern const int iConstExtern;
extern int iStaticGlobal;

//����Ĭ�϶���extern��,�˴���������ʹ��,�Ӳ���extern������,��������,�����extern
void func();

//�����ռ��ڱ���������Ҫ�������ռ��ڰ���
namespace TestLinkage
{
	extern int iExternNameSpace;
	extern int iNameSpace;
	extern int iStaticNameSpace;
}

//thread_local����,�洢�����߳�,ÿ���̶߳���һ���ñ���
thread_local unsigned int rage = 1;
std::mutex cout_mutex;

void increase_rage(const std::string& thread_name)
{
	++rage; // �����޸���û�����;����һ��thread-local ����
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

	//const����Ĭ����static��
	//cout << iConst;
	cout << "iConstExtern define in Test.cpp : " << iConstExtern << endl;

	//������ͷ�ļ��ڵ�const����,����ͷ�ļ��൱���ڱ��ļ����ٴζ�����һ��,��������const����
	//����const��Ĭ��static�Ͳ���ĳ���,������ô��Ҳû����
	cout << "iConstInH define in Test.h : " << iConstInH << endl;

	//static�������ڲ�����,�ⲿ�ļ��޷�����
	//cout << TestLinkage::iStaticNameSpace;
	//cout << iStaticGlobal;

	//�޷�ʹ�ÿ��������ڶ���ı���
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