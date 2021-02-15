#include "Test.h"
#include <windows.h>

//��̬ȫ�ֱ���,�ڲ�����ֻ�ڱ��ļ��ڿɼ�
static int iStaticGlobal = 16;

//������������ռ�������,�����ļ���ֻҪ�����������ռ���ı���,Ҳ����ͨ�������ռ���õķ�ʽ���ñ���
namespace TestLinkage
{
	//static��̬����,�ڲ�����
	static int iStaticNameSpace = 10;
}

//��̬����,ֻ�ڱ��ļ��ڿ���
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
	//������ʱ��ʹ������̸�����
	Sleep(4000);
	std::cout << "Test constructing finished." << std::endl;
}

//��̬��Ա������ʼ��
int Test::m_iStatic = 10;
//��̬��Ա������ʼ��
void Test::FuncStaticB()
{
	m_iStatic++;
	//m_iNonStatic++;
	std::cout << "Static func B in Test class" << std::endl;
}