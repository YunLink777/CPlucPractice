/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/23
 *
 * \brief 模板函数相关demo
 *  \content:
 * 1、模板函数基础，显式模板实参调用；2、显式、隐式实例化；3、模板函数全特化和重载；
 * 4、多模板参数返回值确定（auto和std::common_type）；5、默认模板参数（类型形参和非类型形参）
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//模板函数*****************************************//

//默认模板参数（类型形参和非类型形参）****************************************//

//非类型模板参数的名称和默认值
//下面可以编译成功
// template<class T, int a = 11>  void h(T b) {} 
//下面无法编译成功，因为h(T b, int a = 11)中的a隐藏了模板参数a
//template<class T, int a = 11> void h(T b, int a = 11) {}
//下面可以编译成功
template<class T, int a = 11> void h(T b, int c = 11) {}

int main()
{
	//模板函数*****************************************//

	cout << "****************************" << endl;

	//默认模板参数（类型形参和非类型形参）****************************************//

	//非类型模板参数的名称和默认值
	h(1);
	h<int, 10>(100);//显式实例化指明非类型形参值

	cout << "****************************" << endl;

	system("pause");
	return 0;
}