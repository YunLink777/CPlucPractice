/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/26
 *
 * \brief  �ɱ��ģ�����demo
 *  \content:
 * 1���۵����ʽ��2���ɱ䳤using��
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//�۵����ʽ*****************************************//

//һԪ���ʽ���۵�
template<typename ...T>
auto SubRight(T ... args)
{
	//�����()���Ǳ��ʽ
	//չ����ʽΪargs1 - ... - (argsN-1 - argsN)
	return (args - ...);
}

//һԪ���ʽ���۵�
template<typename ...T>
auto SubLeft(T ... args)
{
	//�����()���Ǳ��ʽ
	//չ����ʽΪargs1 - args2 - ... - argsN
	return (... - args);
}

//��Ԫ���ʽ���۵�
template<typename ...T>
auto OneSubRight(T ... args)
{
	//չ����ʽ�� 1 - args1 - args2 - ... - argsN
	return (1 - ... - args);
}

//��Ԫ���ʽ���۵�
template<typename ...T>
auto LeftSubOne(T ... args)
{
	//չ����ʽ�� args1 - (args2 - ... - (argsN - 1))...)
	return (args - ... - 1);
}

//������������ʽ�۵�,���������Ϊ���ӵĵݹ�չ��
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

//�ղ�����,������&& || , ������������ʽ֮��,���������һԪ���ʽ�Ŀղ���������������
//&& �Ŀղ�����չ�������true, || ��false, ������void()
template<typename ... T>
bool Test(T... args)
{
	cout << "&&: " << (args && ...) << endl
		<< "||: " << (args || ...) << endl;
		//<< ", : " << (args, ...) << endl;
	return true;
}

//�ɱ䳤using*****************************//

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

//C���ؼ̳�T���������ͣ�ͬʱͨ��using������T���������Fun����
template<typename ... T>
class C : public T...
{
public:
	using T::Fun...;
};


int main()
{
	//�۵����ʽ*****************************************//
	//һԪ��������ʽ�۵�
	cout << SubRight(1, 2, 3, 4) << endl;
	cout << SubLeft(1, 2, 3, 4) << endl;
	cout << OneSubRight(2, 3, 4) << endl;
	cout << LeftSubOne(4, 3, 2) << endl;

	cout << "****************************" << endl;

	//������������ʽ�۵�
	PrintDouble(1, 2, 3, 1.1);
	cout << "****************************" << endl;

	//�ղ�����
	Test();

	cout << "****************************" << endl;
	//�ɱ䳤using*****************************//
	//C���ؼ̳�A��B��ͬʱͨ��using������A��B��Fun����
	C<A, B> c;
	c.Fun(1);
	c.Fun(1.1);

	system("pause");
	return 0;
}

