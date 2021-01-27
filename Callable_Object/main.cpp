/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/12
 *
 * \brief �ɵ��ö���Demo
 */
#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

using namespace std;
typedef void(*Say_CallBack)(const string&, const string&);	//ͨ�ຯ��ָ�붨��ص�����
typedef function<void(const string&, const string&)> Say_Function;	//����һ����������
typedef function<void(const string&)> Say_Hi_Function;	

class Person
{
public:
	Person(string s, int a, string x) : xb(x), name(s), age(a) {}
	string GetName() const { return name; }
	int GetAge() const { return age; }
	bool OlderThanAge(int new_age) { return age > new_age; }
	bool OlderThan(const Person& p)
	{
		return age > p.GetAge();
	}
	string xb;

	//------------------------------------------------------------------------
	//ʹ�����ַ�ʽʵ�ֻص�
	void SetSayFun1(Say_CallBack say_callback)
	{
		say_fun1 = say_callback;
	}

	void SetSayFun2(Say_Function say_function)
	{
		say_fun2 = say_function;
	}

	void SetSayHiFun(Say_Hi_Function say_hi_function)
	{
		say_hi_fun = say_hi_function;
	}

	void Say1(const string& word)
	{
		if (say_fun1)
			say_fun1(word, GetName());
	}

	void Say2(const string& word)
	{
		if (say_fun2)
			say_fun2(word, GetName());
	}

	void SayHi()
	{
		if (say_hi_fun)
			say_hi_fun(GetName());
	}

	//------------------------------------------------------------------------
	//��ȡ����ָ����Ϊ�ɵ��ö���
	Say_CallBack GetSayFun1()
	{
		return say_fun1;
	}

	//��ȡstd::function��Ϊ�ɵ��ö���
	Say_Function GetSayFun2()
	{
		return say_fun2;
	}

	//���һ������ָ�룬�˴�ʹ�ú���ָ��������Ϊ����ֵ�����Խ�GetSayFun1_1()����һ������ָ�������������
	void (*GetSayFun1_1())(const string&, const string&)
	{
		return say_fun1;
	}

	//���һ������ָ�룬�˴�ʹ�ú���ָ��������Ϊ����ֵ��->��ʾ����ֵ����
	auto GetSayFun1_2() -> void(*)(const string&, const string&)
	{
		return say_fun1;
	}

	static string Person::* NameData()
	{
		return &Person::name;
	}
private:
	int age;
	string name;
	Say_CallBack say_fun1 = nullptr;
	Say_Function say_fun2 = nullptr;
	Say_Hi_Function say_hi_fun = nullptr;
};

bool OlderThan(const Person& p1, const Person& p2)
{
	return p1.GetAge() > p2.GetAge();
}

void Say_Fun(const string& word, const string& who)
{
	cout << who << " is saying: " << word << endl;
}

//ͨ������()������ʹ������һ���ɵ��ö���
class Older
{
public:
	bool operator() (const Person& a, const Person& b)
	{
		return a.GetAge() > b.GetAge();
	}
};

struct Older_Struct
{
	bool operator() (const Person& a, const Person& b)
	{
		return a.GetAge() > b.GetAge();
	}
};

int main()
{
	Person p("����", 22, "Ů");

	string Person::* ptr = &Person::xb;	//mem pointer
	string* ptrXb = &p.xb;	//a normal pointer point to a exist object's member
	cout << "��Աָ��1: " << p.*ptr << endl;
	cout << "��Աָ��2: " << &p->*ptr << endl;
	cout << "ָ��ĳ�������Ա����ָͨ��: " << *ptrXb << endl;

	string Person::* ptr_static = Person::NameData();
	cout << "��̬��Աָ�룺" << p.*ptr_static << endl;

	int (Person:: * fun_pointer1)() const = &Person::GetAge;	//member function pointer, if the mem f is const, the pointer should be const too
	auto fun_pointer2 = &Person::GetAge;	//use auto keyword, let the complier judge the type
	using fun_GetAge_type = int (Person::*)() const;	//use alias
	fun_GetAge_type fun_pointer3 = &Person::GetAge;	//give the function's address

	cout << "��Ա����ָ��1��" << (p.*fun_pointer1)() << endl;	//the () is necessary
	cout << "��Ա����ָ��2��" << (p.*fun_pointer2)() << endl;
	cout << "��Ա����ָ��3��" << (p.*fun_pointer3)() << endl;

	//------------------------------------------------------------------------
	//But member function pointer is not a callable object, it can only be called by.* or ->*, and it cannot be passed to an algorithm interface
	//So we can use std::function��std::bind��std::mem_fn to encapsulate a member function pointer to a callable object
	//------------------------------------------------------------------------

	//std::function create a callable object, point to member function pointer, the first parameter is the object, it can be a ref or a pointer
	function<int(Person*)> fun1 = &Person::GetAge;	
	cout << "function ��Ա����ָ�룺" << fun1(&p) << endl;
	function<bool(Person&, int)> fun2 = &Person::OlderThanAge;
	cout << "function ��Ա����ָ��2��" << fun2(p, 22) << endl;

	//std::mem_fn encapsulate member function to a callable object, and use auto to judge the type automaticly
	auto fun3 = mem_fn(&Person::OlderThanAge);
	auto data1 = mem_fn(&Person::xb);	//mem_fn can also encapsulate a member variable to a callable object
	cout << "mem_fn ��Ա����ָ��3��" << fun3(&p, 20) << endl;	//mem_fn can use object ref and pointer, it has a overload inside
	cout << "mem_fn ��Ա����ָ��4��" << fun3(p, 20) << endl;
	cout << "mem_fn ��Աָ�룺" << data1(p) << endl;

	//std::bind is much stronger than mem_fn, mem_fn can only encapsulate class members, bind can encapsulate any kind of functions, and can also adapter parameters
	function<int(int)> fun4 = bind(&Person::OlderThanAge, &p, std::placeholders::_1);	//bind is like mem_fn, but it can also adapt the parameters
	auto fun5 = bind(&Person::OlderThanAge, std::placeholders::_1, std::placeholders::_2);
	cout << "bind ��Ա����ָ��5��" << fun4(20) << endl;
	cout << "bind ��Ա����ָ��6��" << fun5(p, 24) << endl;

	//------------------------------------------------------------------------

	//use member function pointer callable object to make sort simpler
	Person p1("����", 20, "Ů");
	Person p2("��һ", 28, "Ů");
	Person p3("���", 50, "Ů");
	Person p4("����", 10, "Ů");
	vector<Person> persons1{p, p1, p2, p3, p4};
	vector<Person> persons2{ p, p1, p2, p3, p4 };
	vector<Person> persons3{ p, p1, p2, p3, p4 };

	//mem_fn(p1, p2)
	sort(persons1.begin(), persons1.end(), mem_fn(&Person::OlderThan));

	//bind(p1, p2)
	sort(persons2.begin(), persons2.end(), bind(&Person::OlderThan, std::placeholders::_1, std::placeholders::_2));

	//function older_fun(p1, p2), but a little complex
	function<bool(Person&, const Person&)> older_fun = &Person::OlderThan;
	sort(persons3.begin(), persons3.end(), older_fun);

	for (auto tempP : persons1)
	{
		cout << "mem_fn   persons: " << tempP.GetName() << " age: "<< tempP.GetAge() << endl;
	}

	cout << endl << endl;

	for (auto tempP : persons2)
	{
		cout << "bind   persons: " << tempP.GetName() << " age: " << tempP.GetAge() << endl;
	}

	cout << endl << endl;

	for (auto tempP : persons3)
	{
		cout << "function   persons: " << tempP.GetName() << " age: " << tempP.GetAge() << endl;
	}

	cout << endl << endl;

	//------------------------------------------------------------------------
	//lambda
	vector<Person> persons4{ p, p1, p2, p3, p4 };
	sort(persons4.begin(), persons4.end(), [](const Person& a, const Person& b)
		{
			return a.GetAge() > b.GetAge();
		});

	for (auto tempP : persons4)
	{
		cout << "lambda   persons: " << tempP.GetName() << " age: " << tempP.GetAge() << endl;
	}

	//lambda  p and p2 are passed as ref, and the lambda expression is caught by function or auto
	function<bool()> older_fun_lambda = [&p, &p2]() { return p.GetAge() > p2.GetAge(); };
	auto fun_auto = [&p, &p2]() { return p.GetAge() > p2.GetAge(); };
	cout << "function lambda   OlderThan: " << older_fun_lambda() << endl;
	cout << "auto lambda   OlderThan: " << fun_auto() << endl;

	cout << endl << endl;

	//a callable object with overload ()
	Older older;
	function<bool(const Person&, const Person&)> older_fun_class = Older();
	function<bool(const Person&, const Person&)> older_fun_struct = Older_Struct();
	cout << "class overload (): " << older(p, p4) << endl;
	cout << "class overload (): " << older_fun_class(p, p4) << endl;
	cout << "struct overload (): " << older_fun_struct(p, p4) << endl;

	//------------------------------------------------------------------------
	//use three way to achieve callback
	p.SetSayFun1(Say_Fun);		//function pointer
	p.SetSayFun2(Say_Fun);		//std::function
	p.SetSayHiFun(bind(Say_Fun, "Hi!", placeholders::_1));	//std::bind, can adapter current function to achieve new function
	p.Say1("Hello!");
	p.Say2("I love you!");
	p.SayHi();

	//bind can change the parameters' order
	p.SetSayFun2(bind(Say_Fun, placeholders::_2, placeholders::_1));
	p.Say2("Hello!");

	cout << endl << endl;
	//------------------------------------------------------------------------
	//function pointer type
	auto fun_get1 = p.GetSayFun1();
	auto fun_get2 = p.GetSayFun1_1();
	auto fun_get3 = p.GetSayFun1_2();
	auto fun_get4 = p.GetSayFun2();

	fun_get1("Hi!", "Lucas");
	fun_get2("Hi!", "Lily");
	fun_get3("Hi!", "Rose");
	fun_get4("Hi!", "Sara");
	
	int i = getchar();
	return 0;
}