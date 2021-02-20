/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/16
 *
 * \brief 面向对象重载、重写（覆盖）、隐藏、多态相关demo
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//重写\覆盖*****************************************//
//重写是中动态多态，是类的多态性
//是通过一个类所有对象共享的虚函数表来实现的
//派生类的虚函数表先拷贝基类的虚函数表，如果派生类重写了某个虚函数，就将虚函数表中该函数地址替换为自己重写的函数地址
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
	//重写(覆盖)必须基类是虚函数,派生类中函数返回值,函数名 参数列表必须一样才行
	void print(int n)
	{
		cout << "Derive print(int)" << endl;
	}

	//参数类型不同是不算重写的,算派生类内部的重载
	void print()
	{
		cout << "Derive print()" << endl;
	}

	//仅返回值类型不同是无法重载的，为了使函数调用上下文无关，不通过返回值判断函数调用类型
	//另外如果和基类里虚函数只有返回值不同,也不算重写,也不是重载,导致编译不过
// 	int print(int n)
// 	{
// 		cout << "Derive int print(int)" << endl;
// 	}
};

//隐藏*****************************************//
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
	//和基类函数名一致,参数一致,不考虑返回值,将隐藏基类函数,即无法通过派生类对象调用基类的此函数
	//如果此时基类此函数是virtual,则是重写,没有,就是隐藏
	//不考虑返回值也是为了使上下文无关
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
	//派生类中函数和基类函数名称相同,参数不同,返回值不考虑,即使基类是虚函数,也被隐藏
	void print()
	{
		cout << "Derive2 print()" << endl;
	}
};

//重载*****************************************//
//重载是中静态多态，是函数的多态性
class Animal
{
public:
	Animal(string name) : name_(name)
	{}

	void Eat(string food)
	{
		cout << name_ << " eat " << food << endl;
	}

	//无法重载只按返回类型区分的函数
	//int Eat(string sFood);

	//重载必须参数不同,返回值可同可不同,函数名必须相同,只有返回值不同而参数相同是无法重载的,为了上下文无关
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

//通过虚函数表调用基类的private函数*****************************************//
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

//运算符重载*****************************************//

int main()
{
	//重写\覆盖*****************************************//
	Derive derive;
	Base* pB = &derive;
	//基类里没有无参数的print,这是派生类内部的重载
	//pB->print();
	//虽然指针是基类指针,但是实际对象是派生类对象,因此根据重写和多态的规则,将调用派生类的方法
	pB->print(0);

	derive.print();
	derive.print(1);

	cout << "****************************" << endl;
	//隐藏*****************************************//
	//隐藏的函数,无法通过基类引用或指针调用,但是可以通过派生类指针调用
	Derive1 derive1;
	Base1* pB1 = &derive1;
	pB1->print(1);
	derive1.print(1);

	Derive2 derive2;
	pB1 = &derive2;
	//已经隐藏了基类的print(int)函数
	//derive2.print(1);
	pB1->print(1);
	derive2.print();

	cout << "****************************" << endl;
	//重载*****************************************//
	Animal cat("Cat");
	cat.Eat("Fish");
	Animal fish("Fish");
	cat.Eat(fish);

	cout << "****************************" << endl;
	//通过虚函数表调用基类的private函数*****************************************//
	B b;
	A a;
	A* pA = &b;

	//无法直接调用A的private函数
	//pA->Func1();
	//pA->Func2();
	//由于虚函数表有所有虚函数的地址，包括private，可以通过直接访问虚函数表中的内容获取private虚函数的指针进行调用
	//&a就是a对象的地址或指针，同时也是虚函数表地址的指针，但类型是A类型的，转换为long long*，就是虚函数表的地址的指针。
	//*(long long*)(&a)就是获得虚函数表的地址，即虚函数表的指针，
	//转换为(long long*)，就是虚函数表开头第一个虚函数的指针， + 1的话就是第二个函数的指针
	Func func1 = (Func)(*(long long*)*(long long*)(&b));
	//调用了A的func1函数
	func1();

	Func func2 = (Func)(*((long long*)*(long long*)(&b) + 1));
	//调用了B的func2函数
	func2();

	//调用了a的func2函数
	Func func3 = (Func)(*((long long*)*(long long*)(&a) + 1));
	func3();

	cout << "****************************" << endl;
	//运算符重载*****************************************//

	system("pause");
	return 0;
}