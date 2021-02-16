/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \brief 面向对象基础demo
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Test
{
public:
	Test(int i, float f, bool b)
		: m_i(i)
		, m_f(f)
		, m_b(b)
	{}

	int m_i;
	float m_f;
	bool m_b;
};

int main()
{
	//可以通过大括号初始化对象，大括号内变量的顺序需要在某个该类构造函数中一致
	Test test{ 0, 1.1f, false };
	//可以通过大括号初始化向量等数据结构
	vector<Test> vectors = { {0, 1.1, false}, {1, 2.1, true}, {4, 3.1, true} };
	cout << vectors.size() << endl;
	system("pause");
	return 0;
}