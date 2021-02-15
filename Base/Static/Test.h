#ifndef TEST_H
#define TEST_H

#include <iostream>

class Test
{
public:
	Test();
	//静态成员变量,每个类有一个实例,不依赖类实例化而存在,全对象共享
	static int m_iStatic;
	int m_iNonStatic = 0;

	//静态成员函数,不依赖类实例化而存在,只能调用静态成员变量
	static void FuncStaticA()
	{
		m_iStatic++;
		//m_iNonStatic++;
		std::cout << "Static func A in Test class" << std::endl;
	}

	static void FuncStaticB();
};
#endif
