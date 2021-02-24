/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/23
 *
 * \brief 模板类相关demo
 *  \content:
 * 1、模板类基础，显式模板实参调用；2、显式、隐式实例化、成员函数实例化时机；3、concept和static_assert
 * 4、模板类的友元函数和友元类（两种声明方式区别）
 * 5、模板类的全特化、半特化、半特化为另一个模板类
 * 6、默认模板参数；7、using、typedef、typename别名
 * 7、deduced guides 推断指导规则
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//模板类*****************************************//
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
	//模板类*****************************************//
	
	cout << "****************************" << endl;
	system("pause");
	return 0;
}