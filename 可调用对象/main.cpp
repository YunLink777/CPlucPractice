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
	Person p("����", 22, "Ů");

	string Person::* ptr = &Person::xb;	//��Աָ��
	cout << "��Աָ��1: " << p.*ptr << endl;
	cout << "��Աָ��2: " << &p->*ptr << endl;

	string Person::* ptr_static = Person::NameData();
	cout << "��̬��Աָ�룺" << p.*ptr_static << endl;

	int (Person:: * fun_pointer1)() const = &Person::GetAge;	//��Ա����ָ�룬�����const��Ա����������ָ��ʱҲҪ����const
	auto fun_pointer2 = &Person::GetAge;	//ʹ��auto�ؼ��֣��ñ������Լ��ж�����
	using fun_GetAge = int (Person::*)() const;	//ʹ�ñ���
	fun_GetAge fun_pointer3 = &Person::GetAge;	//ָ��������ַ

	cout << "��Ա����ָ��1��" << (p.*fun_pointer1)() << endl;	//����ʱ�������()
	cout << "��Ա����ָ��2��" << (p.*fun_pointer2)() << endl;
	cout << "��Ա����ָ��3��" << (p.*fun_pointer3)() << endl;

	function<int(Person*)> fun1 = &Person::GetAge;	//function����һ���ɵ��õĶ���ָ���Ա����ָ�룬��һ������Ϊ���ö��󣬿���������Ҳ������ָ��
	cout << "function ��Ա����ָ�룺" << fun1(&p) << endl;
	function<bool(Person&, int)> fun2 = &Person::OlderThan;
	cout << "function ��Ա����ָ��2��" << fun2(p, 22) << endl;

	auto fun3 = mem_fn(&Person::OlderThan);	//mem_fn��װ��Ա����Ϊһ���ɵ��ö��������Զ��ж�
	auto data1 = mem_fn(&Person::xb);	//mem_fnҲ���Խ���Ա������װΪһ���ɵ��ö���
	cout << "mem_fn ��Ա����ָ��3��" << fun3(&p, 20) << endl;
	cout << "mem_fn ��Ա����ָ��4��" << fun3(p, 20) << endl;
	cout << "mem_fn ��Աָ�룺" << data1(p) << endl;

	function<int(int)> fun4 = bind(&Person::OlderThan, &p, std::placeholders::_1);	//bind��mem_fn���ƣ����ǿ����������
	auto fun5 = bind(&Person::OlderThan, std::placeholders::_1, std::placeholders::_2);	
	cout << "bind ��Ա����ָ��5��" << fun4(20) << endl;
	cout << "bind ��Ա����ָ��6��" << fun5(p, 24) << endl;

	//TODO ����mem_fn����sort�����㷨ʹ�õıȽϺ���
	getchar();
	return 0;
}