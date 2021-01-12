/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/12
 *
 * \description:Callable Objects
 */
#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

using namespace std;

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

	static string Person::* NameData()
	{
		return &Person::name;
	}
private:
	int age;
	string name;
};

bool OlderThan(const Person& p1, const Person& p2)
{
	return p1.GetAge() > p2.GetAge();
}

int main()
{
	Person p("����", 22, "Ů");

	string Person::* ptr = &Person::xb;	//mem pointer
	cout << "��Աָ��1: " << p.*ptr << endl;
	cout << "��Աָ��2: " << &p->*ptr << endl;

	string Person::* ptr_static = Person::NameData();
	cout << "��̬��Աָ�룺" << p.*ptr_static << endl;

	int (Person:: * fun_pointer1)() const = &Person::GetAge;	//member function pointer, if the mem f is const, the pointer should be const too
	auto fun_pointer2 = &Person::GetAge;	//use auto keyword, let the complier judge the type
	using fun_GetAge = int (Person::*)() const;	//use alias
	fun_GetAge fun_pointer3 = &Person::GetAge;	//give the function's address

	cout << "��Ա����ָ��1��" << (p.*fun_pointer1)() << endl;	//the () is necessary
	cout << "��Ա����ָ��2��" << (p.*fun_pointer2)() << endl;
	cout << "��Ա����ָ��3��" << (p.*fun_pointer3)() << endl;

	//function create a callable object, point to member function pointer, the first parameter is the object, it can be a ref or a pointer
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

	function<int(int)> fun4 = bind(&Person::OlderThanAge, &p, std::placeholders::_1);	//bind is like mem_fn, but it can also adapt the parameters
	auto fun5 = bind(&Person::OlderThanAge, std::placeholders::_1, std::placeholders::_2);
	cout << "bind ��Ա����ָ��5��" << fun4(20) << endl;
	cout << "bind ��Ա����ָ��6��" << fun5(p, 24) << endl;

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
		cout << "persons: " << tempP.GetName() << " age: "<< tempP.GetAge() << endl;
	}

	cout << endl << endl;

	for (auto tempP : persons2)
	{
		cout << "persons: " << tempP.GetName() << " age: " << tempP.GetAge() << endl;
	}

	cout << endl << endl;

	for (auto tempP : persons3)
	{
		cout << "persons: " << tempP.GetName() << " age: " << tempP.GetAge() << endl;
	}

	cout << endl << endl;
	
	getchar();
	return 0;
}