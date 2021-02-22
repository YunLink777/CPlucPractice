/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/22
 *
 * \brief 模板基础相关demo
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//模板函数*****************************************//
//模板形参有类型模板形参(T,U),其中U提供默认类型int, 还有非类型模板形参(time),提供默认值
template<typename T, typename U = int, int time = 1>
void PrintMulti(const T& content, U num)
{
	int tempTime = time;
	if (tempTime < 1)
	{
		tempTime = 1;
	}
	for (int i = 0; i < tempTime; i++)
	{
		cout << content << " " << num << endl;
	}
}

//模板类*****************************************//
//MAXNUM必须是int、指针类型的常量,编译时可获得值
//全局变量、全局对象的地址、const变量、sizeof表达式可以
//如果是指针，则这个指针本身是常量，指向的内容可以不是常量
template<typename T, int MAXNUM>
class Stack
{
private:
	T elements[MAXNUM];
	int element_num;

public:
	Stack();
	void Push(const T& t);
	void Pop();
	T Top();
	bool Empty()
	{
		return element_num == 0;
	}
	bool Full()
	{
		return element_num == MAXNUM;
	}
};

template<typename T, int MAXNUM>
Stack<T, MAXNUM>::Stack()
{
	element_num = 0;
}

template<typename T, int MAXNUM>
void Stack<T, MAXNUM>::Push(const T& t)
{
	if (element_num == MAXNUM)
	{
		//抛出异常,不再继续执行
		throw std::out_of_range("Stack<>::Push(): stack is full");
	}

	elements[element_num] = t;
	element_num++;
}

template<typename T, int MAXNUM>
void Stack<T, MAXNUM>::Pop()
{
	if (Empty())
	{
		throw::std::out_of_range("Stack<>::Pop(): Empty stack");
	}

	element_num--;
}

template<typename T, int MAXNUM>
T Stack<T, MAXNUM>::Top()
{
	if (Empty())
	{
		throw::std::out_of_range("Stack<>::Top(): Empty stack");
	}

	return elements[element_num - 1];
}

int main()
{
	//模板函数*****************************************//
	PrintMulti("Test PrintMulti", 100);
	PrintMulti<string, int, 4>("Test PrintMulti 4 times", 100.1);

	cout << "****************************" << endl;

	//模板类*****************************************//
	Stack<int, 10> stack1;
	for (int i = 0; i < 10; i++)
	{
		stack1.Push(i);
	}

	const int size = 2;
	Stack<float, size> stack2;
	cout << "****************************" << endl;

	system("pause");
	return 0;
}