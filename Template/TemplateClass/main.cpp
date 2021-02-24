/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/23
 *
 * \brief ģ�������demo
 *  \content:
 * 1��ģ�����������ʽģ��ʵ�ε��ã�2����ʽ����ʽʵ��������Ա����ʵ����ʱ����3��concept��static_assert
 * 4��ģ�������Ԫ��������Ԫ�ࣨ����������ʽ����
 * 5��ģ�����ȫ�ػ������ػ������ػ�Ϊ��һ��ģ����
 * 6��Ĭ��ģ�������7��using��typedef��typename����
 * 7��deduced guides �ƶ�ָ������
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//ģ����*****************************************//
template<typename T, typename U>
class Pair
{
private:
	vector<T> first_;
	vector<U> second_;

public:
	Pair() = default;
	Pair(const Pair& pair);
	Pair(Pair&& pair);

	void operator= (const Pair& pair);
	void operator= (Pair&& pair);
};

template<typename T, typename U>
Pair<T, U>::Pair(const Pair& pair)
{

}

template<typename T, typename U>
Pair<T, U>::Pair(Pair&& pair)
{

}

template<typename T, typename U>
void Pair<T, U>::operator=(const Pair& pair)
{}

template<typename T, typename U>
void Pair<T, U>::operator=(Pair&& pair)
{}

int main()
{
	//ģ����*****************************************//
	
	cout << "****************************" << endl;
	system("pause");
	return 0;
}