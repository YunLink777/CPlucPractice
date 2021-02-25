/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/23
 *
 * \brief 模板类相关demo
 *  \content:
 * 1、模板类基础；2、显式、隐式实例化、成员函数实例化时机
 * 3、模板类的友元函数和友元类（两种声明方式区别）
 * 4、模板类的全特化、半特化、半特化为另一个模板类
 * 5、deduced guides 推断指导规则
 * 6、concept
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//模板类*****************************************//

//友元模板函数和友元模板类*****************************************//
template<typename T, typename U>
class Pair;

template<typename T, typename U>
class A
{
public:
	void Test()
	{
		Pair<int, int> p;
		//访问Pair<int,int>的private成员变量, 如果实例化Test,会编译错误
		int a = p.first_;
	}
};

//绑定的友元模板函数，此处是声明和定义，要先声明和定义
//template<typename T, typename U>
//class Pair;
//
//template<typename T, typename U>
//ostream& operator<< (ostream& os, const Pair<T, U>& pair)
//{
//	os << pair.first_ << " : " << pair.second_;
//	Pair<int, int> p(1, 2);
//	//由于是1对1绑定的友元模板函数，所以无法访问<int,int>类型的private成员
//	//cout << p.first_;
//	return os;
//}

template<typename T, typename U>
class Pair
{
private:
	T first_;
	U second_;

public:
	Pair() = default;
	Pair(const Pair& pair);
	Pair(T first, U second);

	T& first();
	U& second();
	void set_first(T first);
	void set_second(U second);

	void operator= (const Pair& pair);

	//多对多的非绑定的友元模板函数，即v、w可以和T和U不同，operator<< <string, int>可以是Pair<double, float>的友元
	template<typename V, typename W>
	friend ostream& operator<< (ostream& os, const Pair<V, W>& pair);

	//一对一的绑定的友元模板函数，此时operator<< <string, int>只能是Pair<string,int>的友元，注意此处声明operator<<后要有<T, U>，说明此处友元模板函数已经实例化
	//friend ostream& operator<<<T, U> (ostream& os, const Pair<T, U>& pair);

	//多对多的非绑定友元模板类，A不用提前声明
// 	template<typename T, typename U>
// 	friend class A;

	//一对一的绑定的友元模板类 A要提前声明
	friend class A<T, U>;
};

template<typename T, typename U>
void Pair<T, U>::set_second(U second)
{
	second_ = second;
}

template<typename T, typename U>
void Pair<T, U>::set_first(T first)
{
	first_ = first;
}

template<typename T, typename U>
U& Pair<T, U>::second()
{
	return second_;
}

template<typename T, typename U>
T& Pair<T, U>::first()
{
	return first_;
}

template<typename T, typename U>
Pair<T, U>::Pair(T first, U second)
{
	first_ = first;
	second_ = second;
}

template<typename T, typename U>
Pair<T, U>::Pair(const Pair& pair)
{
	first_ = pair.first_;
	second_ = pair.second_;
}

template<typename T, typename U>
void Pair<T, U>::operator=(const Pair& pair)
{
	first_ = pair.first_;
	second_ = pair.second_;
}

template<typename T, typename U>
ostream& operator<< (ostream& os, const Pair<T, U>& pair)
{
	os << pair.first_ << " : " << pair.second_;
	Pair<int, int> p(1, 2);
	//由于是多对多的友元模板函数，可以访问此类型的private成员
	cout << p.first_;
	return os;
}

//  template<typename T, typename U>
//  class A
//  {
//  public:
//  	void Test()
//  	{
//  		Pair<int, int> p(0,0);
//  		int a = p.first_;
//  	}
//  };

//类模板的显式实例化，会实例化类的所有成员，包括函数，而不是像隐式实例化一样，只有成员函数调用时才实例化成员函数
//此处会编译错误，因为友元模板类是一一对应的
//template class A<string, int>;

//类型推到指引,将Pair(const char*, double)推到为 Pair<string, int>类型
Pair(const char*, double) -> Pair<string, int>;

//模板类特化、半特化*****************************************//
//全特化
template<>
class Pair<double, double>
{
private:
	double first_;
	double second_;

public:
	Pair() = default;
	Pair(const Pair & pair);
	Pair(double first, double second);

	double& first();
	double& second();
	void set_first(double first);
	void set_second(double second);

	void operator= (const Pair & pair);

	template<typename V, typename W>
	friend ostream& operator<< (ostream & os, const Pair<V, W>&pair);

	friend class A<double, double>;
};

Pair<double, double>::Pair(const Pair<double, double>& pair)
{
	first_ = pair.second_;
	second_ = pair.first_;
}

Pair<double, double>::Pair(double first, double second)
{
	first_ = first;
	second_ = second;
}

//其他成员函数暂不特化

//半特化, 也可以半特化为T* 或T&类型
template<typename T>
class Pair<T, string>
{
private:
	T first_;
	string second_;

public:
	Pair() = default;
	Pair(const Pair& pair);
	Pair(T first, string second);

	T& first();
	string& second();
	void set_first(T first);
	void set_second(string second);

	void operator= (const Pair& pair);

	template<typename V, typename W>
	friend ostream& operator<< (ostream& os, const Pair<V, W>& pair);

	friend class A<T, string>;
};

template<typename T>
Pair<T, string>::Pair(const Pair<T, string>& pair)
{
	first_ = pair.first_ + 1;
	second_ = pair.second_ + " second";
}

template<typename T>
Pair<T, string>::Pair(T first, string second)
{
	first_ = first;
	second_ = second;
}

//半特化为另一个模板类
template<typename T>
class Pair<T, vector<T>>
{
private:
	T first_;
	vector<T> second_;

public:
	Pair() = default;
	Pair(const Pair& pair);
	Pair(T first, vector<T> second);

	T& first();
	vector<T>& second();
	void set_first(T first);
	void set_second(vector<T> second);

	void operator= (const Pair& pair);

	template<typename V, typename W>
	friend ostream& operator<< (ostream& os, const Pair<V, W>& pair);

	friend class A<T, string>;
};

template<typename T>
Pair<T, vector<T>>::Pair(const Pair<T, vector<T> >& pair)
{
	first_ = pair.first_ + 1;
	second_ = pair.second_;
	second_.push_back(first_);
}

template<typename T>
Pair<T, vector<T>>::Pair(T first, vector<T> second)
{
	first_ = first;
	second_ = second;
}

template<typename T>
vector<T>& Pair<T, vector<T> >::second()
{
	return second_;
}

//concept约束*****************************************//
template<typename T>
concept Integral = std::is_integral_v<T>;

template<Integral T>
class Test
{
private:
	T value_;
};

int main()
{
	//模板类*****************************************//
	Pair<string, int> pair1;
	Pair<string, int> pair2("Age", 20);
	Pair<string, int> pair3 = pair2;
	pair1 = pair2;
	pair2.set_first("Grade");
	pair2.set_second(100);
	cout << pair1 << endl;
	cout << pair2 << endl;
	cout << pair3 << endl;

	//隐式实例化只完成类的定义，成员函数还没实例化
	A<string, int> a;

	//如果模板类是隐式实例化，模板类的成员函数只有调用时才实例化
	//实例化后, 发现A<string, int>无法访问Pair<int,int>的private成员,因为是一对一绑定的模板友元类
	//a.Test();

	//类型推到指引,将Pair(const char*, double)推到为 Pair<string, int>类型, 输出是int类型
	Pair pair4("test", 1.111);
	cout << pair4 << endl;

	cout << "****************************" << endl;

	//特化的Pair<double, double>类型
	Pair<double, double> pair5(1.11, 2.22);
	Pair<double, double> pair6 = pair5;
	cout << pair5 << pair6 << endl;

	//半特化的Pair<T, string>类型
	Pair<double, string> pair7(1.11, "double");
	Pair<double, string> pair8 = pair7;
	cout << pair7 << pair8 << endl;

	//半特化的Pair<T, vector<T> >类型
	Pair<double, vector<double> > pair9(1.11, {2.2, 3.3});
	Pair<double, vector<double> > pair10 = pair9;
	vector<double> second = pair10.second();
	for (auto a : second)
	{
		cout << a << endl;
	}
	cout << "****************************" << endl;

	//concept已经约束了T必须是整数型的，double会无法通过编译
	//Test<double> test;
	Test<int> test;
	Test<long> test;
	

	system("pause");
	return 0;
}