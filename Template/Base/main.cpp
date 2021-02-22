/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/22
 *
 * \brief ģ��������demo
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//ģ�庯��*****************************************//
//ģ���β�������ģ���β�(T,U),����U�ṩĬ������int, ���з�����ģ���β�(time),�ṩĬ��ֵ
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

//ģ����*****************************************//
//MAXNUM������int��ָ�����͵ĳ���,����ʱ�ɻ��ֵ
//ȫ�ֱ�����ȫ�ֶ���ĵ�ַ��const������sizeof���ʽ����
//�����ָ�룬�����ָ�뱾���ǳ�����ָ������ݿ��Բ��ǳ���
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
		//�׳��쳣,���ټ���ִ��
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
	//ģ�庯��*****************************************//
	PrintMulti("Test PrintMulti", 100);
	PrintMulti<string, int, 4>("Test PrintMulti 4 times", 100.1);

	cout << "****************************" << endl;

	//ģ����*****************************************//
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