#ifndef TEST_H
#define TEST_H

#include <iostream>

class Test
{
public:
	Test();
	//��̬��Ա����,ÿ������һ��ʵ��,��������ʵ����������,ȫ������
	static int m_iStatic;
	int m_iNonStatic = 0;

	//��̬��Ա����,��������ʵ����������,ֻ�ܵ��þ�̬��Ա����
	static void FuncStaticA()
	{
		m_iStatic++;
		//m_iNonStatic++;
		std::cout << "Static func A in Test class" << std::endl;
	}

	static void FuncStaticB();
};
#endif
