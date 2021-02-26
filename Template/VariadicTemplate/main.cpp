/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/26
 *
 * \brief  可变参模板相关demo
 *  \content:
 * 1、折叠表达式；2、可变长using；
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//折叠表达式*****************************************//

//一元表达式右折叠
template<typename ...T>
auto SubRight(T ... args)
{
	//必须加()才是表达式
	//展开形式为args1 - ... - (argsN-1 - argsN)
	return (args - ...);
}

//一元表达式左折叠
template<typename ...T>
auto SubLeft(T ... args)
{
	//必须加()才是表达式
	//展开形式为args1 - args2 - ... - argsN
	return (... - args);
}

//二元表达式左折叠
template<typename ...T>
auto OneSubRight(T ... args)
{
	//展开形式是 1 - args1 - args2 - ... - argsN
	return (1 - ... - args);
}

//二元表达式右折叠
template<typename ...T>
auto LeftSubOne(T ... args)
{
	//展开形式是 args1 - (args2 - ... - (argsN - 1))...)
	return (args - ... - 1);
}

//逗号运算符表达式折叠,可以替代较为复杂的递归展开
template<typename T>
void Print(T t)
{
	std::cout << t << std::endl;
}

template <typename... T>
void  PrintDouble(T const& ... args)
{
	(Print(2 * args), ...);
}

//空参数包,除了了&& || , 三个运算符表达式之外,其他运算符一元表达式的空参数包都会编译错误
//&& 的空参数包展开结果是true, || 是false, 逗号是void()
template<typename ... T>
bool Test(T... args)
{
	cout << "&&: " << (args && ...) << endl
		<< "||: " << (args || ...) << endl;
		//<< ", : " << (args, ...) << endl;
	return true;
}

//可变长using*****************************//

class A
{
public:
	void Fun(int i)
	{
		cout << "A::Fun" << endl;
	}
};

class B 
{
public:
	void Fun(double d)
	{
		cout << "B::Fun" << endl;
	}
};

//C多重继承T的所有类型，同时通过using声明了T中所有类的Fun函数
template<typename ... T>
class C : public T...
{
public:
	using T::Fun...;
};


int main()
{
	//折叠表达式*****************************************//
	//一元运算符表达式折叠
	cout << SubRight(1, 2, 3, 4) << endl;
	cout << SubLeft(1, 2, 3, 4) << endl;
	cout << OneSubRight(2, 3, 4) << endl;
	cout << LeftSubOne(4, 3, 2) << endl;

	cout << "****************************" << endl;

	//逗号运算符表达式折叠
	PrintDouble(1, 2, 3, 1.1);
	cout << "****************************" << endl;

	//空参数包
	Test();

	cout << "****************************" << endl;
	//可变长using*****************************//
	//C多重继承A，B，同时通过using声明了A和B的Fun函数
	C<A, B> c;
	c.Fun(1);
	c.Fun(1.1);

	system("pause");
	return 0;
}

