#include <iostream>
#include <functional>
#include <string>

using namespace std;

class Person
{
public:
	Person(string s, int a, string x) : xb(x), name(s), age(a) {}
	string GetName() const { return name; }
	int GetAge() const { return age; }
	bool OlderThan(int new_age) { return age > new_age; }
	string xb;

	static string Person::* NameData()
	{
		return &Person::name;
	}
private:
	int age;
	string name;
};

int main()
{
	Person p("张三", 22, "女");

	string Person::* ptr = &Person::xb;	//成员指针
	cout << "成员指针1: " << p.*ptr << endl;
	cout << "成员指针2: " << &p->*ptr << endl;

	string Person::* ptr_static = Person::NameData();
	cout << "静态成员指针：" << p.*ptr_static << endl;

	int (Person:: * fun_pointer1)() const = &Person::GetAge;	//成员函数指针，如果是const成员函数，声明指针时也要加上const
	auto fun_pointer2 = &Person::GetAge;	//使用auto关键字，让编译器自己判断类型
	using fun_GetAge = int (Person::*)() const;	//使用别名
	fun_GetAge fun_pointer3 = &Person::GetAge;	//指定函数地址

	cout << "成员函数指针1：" << (p.*fun_pointer1)() << endl;	//调用时必须加上()
	cout << "成员函数指针2：" << (p.*fun_pointer2)() << endl;
	cout << "成员函数指针3：" << (p.*fun_pointer3)() << endl;

	function<int(Person*)> fun1 = &Person::GetAge;	//function生成一个可调用的对象，指向成员函数指针，第一个参数为调用对象，可以是引用也可以是指针
	cout << "function 成员函数指针：" << fun1(&p) << endl;
	function<bool(Person&, int)> fun2 = &Person::OlderThan;
	cout << "function 成员函数指针2：" << fun2(p, 22) << endl;

	auto fun3 = mem_fn(&Person::OlderThan);	//mem_fn封装成员函数为一个可调用对象，类型自动判断
	auto data1 = mem_fn(&Person::xb);	//mem_fn也可以将成员变量封装为一个可调用对象
	cout << "mem_fn 成员函数指针3：" << fun3(&p, 20) << endl;
	cout << "mem_fn 成员函数指针4：" << fun3(p, 20) << endl;
	cout << "mem_fn 成员指针：" << data1(p) << endl;

	function<int(int)> fun4 = bind(&Person::OlderThan, &p, std::placeholders::_1);	//bind和mem_fn类似，但是可以适配参数
	auto fun5 = bind(&Person::OlderThan, std::placeholders::_1, std::placeholders::_2);	
	cout << "bind 成员函数指针5：" << fun4(20) << endl;
	cout << "bind 成员函数指针6：" << fun5(p, 24) << endl;

	//TODO 根据mem_fn生成sort排序算法使用的比较函数
	getchar();
	return 0;
}