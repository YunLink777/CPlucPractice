/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \brief ����������ء���д�����ǣ������ء���̬���demo
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//��д\����*****************************************//
//��д���ж�̬��̬������Ķ�̬��
//��ͨ��һ�������ж�������麯������ʵ�ֵ�
//��������麯�����ȿ���������麯���������������д��ĳ���麯�����ͽ��麯�����иú�����ַ�滻Ϊ�Լ���д�ĺ�����ַ
class Base
{
public:
	virtual void print(int n)
	{
		cout << "Base print(int)" << endl;
	}
};

class Derive : public Base
{
public:
	//��д(����)����������麯��,�������к�������ֵ,������ �����б����һ������
	void print(int n)
	{
		cout << "Derive print(int)" << endl;
	}

	//�������Ͳ�ͬ�ǲ�����д��,���������ڲ�������
	void print()
	{
		cout << "Derive print()" << endl;
	}

	//������ֵ���Ͳ�ͬ���޷����صģ�Ϊ��ʹ���������������޹أ���ͨ������ֵ�жϺ�����������
	//��������ͻ������麯��ֻ�з���ֵ��ͬ,Ҳ������д,Ҳ��������,���±��벻��
// 	int print(int n)
// 	{
// 		cout << "Derive int print(int)" << endl;
// 	}
};

//����*****************************************//
class Base1
{
public:
	void print(int n)
	{
		cout << "Base1 print(int)" << endl;
	}
};

class Derive1 : public Base1
{
public:
	//�ͻ��ຯ����һ��,����һ��,�����Ƿ���ֵ,�����ػ��ຯ��,���޷�ͨ�������������û���Ĵ˺���
	//�����ʱ����˺�����virtual,������д,û��,��������
	//�����Ƿ���ֵҲ��Ϊ��ʹ�������޹�
	//int print(int n)
	void print(int n)
	{
		cout << "Derive1 print(int)" << endl;
		//return 1;
	}
};

class Derive2 : public Base1
{
public:
	//�������к����ͻ��ຯ��������ͬ,������ͬ,����ֵ������,��ʹ�������麯��,Ҳ������
	void print()
	{
		cout << "Derive2 print()" << endl;
	}
};

//����*****************************************//
//�������о�̬��̬���Ǻ����Ķ�̬��
class Animal
{
public:
	Animal(string name) : name_(name)
	{}

	void Eat(string food)
	{
		cout << name_ << " eat " << food << endl;
	}

	//�޷�����ֻ�������������ֵĺ���
	//int Eat(string sFood);

	//���ر��������ͬ,����ֵ��ͬ�ɲ�ͬ,������������ͬ,ֻ�з���ֵ��ͬ��������ͬ���޷����ص�,Ϊ���������޹�
	int Eat(Animal animal)
	{
		cout << name_ << " eat " << animal.name_ << endl;
		return 0;
	}

	void Eat(const char* pFood)
	{
		cout << name_ << " eat " << pFood << endl;
	}

	string name_;
};

//ͨ���麯������û����private����*****************************************//
using Func = void(*)();
class A
{
private:
	virtual void Func1()
	{
		cout << "A Func1" << endl;
	}

	virtual void Func2()
	{
		cout << "A Func2" << endl;
	}
};

class B : public A
{
public:
	virtual void Func2()
	{
		cout << "B Func2" << endl;
	}
};

//���������*****************************************//

int main()
{
	//��д\����*****************************************//
	Derive derive;
	Base* pB = &derive;
	//������û���޲�����print,�����������ڲ�������
	//pB->print();
	//��Ȼָ���ǻ���ָ��,����ʵ�ʶ��������������,��˸�����д�Ͷ�̬�Ĺ���,������������ķ���
	pB->print(0);

	derive.print();
	derive.print(1);

	cout << "****************************" << endl;
	//����*****************************************//
	//���صĺ���,�޷�ͨ���������û�ָ�����,���ǿ���ͨ��������ָ�����
	Derive1 derive1;
	Base1* pB1 = &derive1;
	pB1->print(1);
	derive1.print(1);

	Derive2 derive2;
	pB1 = &derive2;
	//�Ѿ������˻����print(int)����
	//derive2.print(1);
	pB1->print(1);
	derive2.print();

	cout << "****************************" << endl;
	//����*****************************************//
	Animal cat("Cat");
	cat.Eat("Fish");
	Animal fish("Fish");
	cat.Eat(fish);

	cout << "****************************" << endl;
	//ͨ���麯������û����private����*****************************************//
	B b;
	A a;
	A* pA = &b;

	//�޷�ֱ�ӵ���A��private����
	//pA->Func1();
	//pA->Func2();
	//�����麯�����������麯���ĵ�ַ������private������ͨ��ֱ�ӷ����麯�����е����ݻ�ȡprivate�麯����ָ����е���
	//&a����a����ĵ�ַ��ָ�룬ͬʱҲ���麯�����ַ��ָ�룬��������A���͵ģ�ת��Ϊlong long*�������麯����ĵ�ַ��ָ�롣
	//*(long long*)(&a)���ǻ���麯����ĵ�ַ�����麯�����ָ�룬
	//ת��Ϊ(long long*)�������麯����ͷ��һ���麯����ָ�룬 + 1�Ļ����ǵڶ���������ָ��
	Func func1 = (Func)(*(long long*)*(long long*)(&b));
	//������A��func1����
	func1();

	Func func2 = (Func)(*((long long*)*(long long*)(&b) + 1));
	//������B��func2����
	func2();

	//������a��func2����
	Func func3 = (Func)(*((long long*)*(long long*)(&a) + 1));
	func3();

	cout << "****************************" << endl;
	//���������*****************************************//

	system("pause");
	return 0;
}