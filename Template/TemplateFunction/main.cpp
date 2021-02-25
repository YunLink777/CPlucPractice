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
 * 5、模板函数的半特化
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//模板函数*****************************************//
//返回类型auto，根据实际情况确定返回类型
template<typename T, typename U>
auto Max(T t, U u)
{
	cout << "Max<T, U>" << endl;
	return t > u ? t : u;
}

//显式实例化
template auto Max<float, float>(float, float);

//模板函数全特化
template<>
auto Max<int, double>(int a, double b)
{
	cout << "Max<int, double>" << endl;
	return a > b ? a : b;
}

//模板函数重载
int Max(int a, int b)
{
	cout << "Max(int, int)" << endl;
	return a > b ? a : b;
}

template<typename T, typename U>
std::common_type_t<T, U> Min(T t, U u)
{
	return t > u ? u : t;
}

//默认模板参数（类型形参和非类型形参）****************************************//
//类型形参的默认值
//template<typename T, typename Ts>//没有给Ts赋默认值, 调用print(1)会编译错误
template<typename T, typename Ts = ostream>
void print(T input, Ts& os = cout) {
	os << input << endl;
}

//非类型模板参数的名称和默认值
//下面可以编译成功
// template<class T, int a = 11>  void h(T b) {} 
//下面无法编译成功，因为h(T b, int a = 11)中的a隐藏了模板参数a
//template<class T, int a = 11> void h(T b, int a = 11) {}
//下面可以编译成功
template<class T, int a = 11> void h(T b, int c = 11) {}

//模板函数偏特化(使用concept实现)****************************************//
template<typename T, typename U>
void PrintNew(T t, U u)
{
	cout << "PrintNew<T, U> " << t << " " << u << endl;
}

template<typename T, typename U>
requires std::integral<U>	//要求U是int类型
void PrintNew(T t, U u)
{
	cout << "PrintNew<T, int> " << t << " " << u << endl;
}


int main()
{
	//模板函数*****************************************//
	cout << Max(1.1f, 2.2f) << endl;

	//隐式实例化
	//隐式调用
	cout << Max(1, 1.1f) << endl;

	//显式模板实参调用
	cout << Max<string, string>("abc", "def") << endl;

	//全特化
	cout << Max(1, 2.2) << endl;
	cout << Max<int, double>(5.1, 2) << endl;

	//重载，若类型精度一致，优先调用普通函数
	cout << Max(1, 2) << endl;
	//若函数模板匹配更好，优先调用模板函数
	cout << Max(1, 2l) << endl;
	//可强制调用模板函数
	cout << Max<>(1, 2) << endl;

	//std::common_type
	cout << Min(1, 10.0f) << endl;

	cout << "****************************" << endl;

	//默认模板参数（类型形参和非类型形参）****************************************//
	//类型形参的默认值
	print(1);

	//非类型模板参数的名称和默认值
	h(1);
	h<int, 10>(100);//显式实例化指明非类型形参值

	cout << "****************************" << endl;

	//模板函数偏特化(使用concept实现)****************************************//
	PrintNew(1, 1.1);
	PrintNew(1, 2);

	system("pause");
	return 0;
}

