/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \brief ����������demo
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
	//����ͨ�������ų�ʼ�����󣬴������ڱ�����˳����Ҫ��ĳ�����๹�캯����һ��
	Test test{ 0, 1.1f, false };
	//����ͨ�������ų�ʼ�����������ݽṹ
	vector<Test> vectors = { {0, 1.1, false}, {1, 2.1, true}, {4, 3.1, true} };
	cout << vectors.size() << endl;
	system("pause");
	return 0;
}