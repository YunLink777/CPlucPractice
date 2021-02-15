/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/15
 *
 * \brief const volatile auto ,����ת�������demo
 */

#include <iostream>

using namespace std;

//const���κ�������ֵ���������������ͣ���û��const��һ��
//�������Զ������ͻ�������ָ��,�򷵻صľ��ǳ���
const int add(int t, int u)
{
	const int i = t + u;
	return i;
}

const int* sub(int a, int b, int * c)
{
     *c = a - b;
     return c;
}

int func()
{
    cout << "func runing" << endl;
    return 0;
}

int funcA()
{
    return 1;
}

class Base {

 public:
     Base() :str(nullptr) {}
     Base(string s) : str(s) {}
     virtual void print()
     {
         cout << str << "  ";
     }
 private:
     string str;

};

class Derived :public Base

 {
 public:
     Derived() {}
     Derived(string s, int i) :Base(s), ival(i) {}
     void print()
     {
         Base::print();
         cout << ival << endl;
     }
     void print_ival()
     {
         cout << "�����ival��ֵ��" << ival << endl;
     }
 private:
     int ival;
 };

int main()
{
	const int a = 10; // a ����Ϊһ������
    const int b = 11;

	int* p = nullptr;
	p = (int*)&a;  //�˴�ȡa �ĵ�ַ����C++�ᵥ������һ���µ��ڴ�ռ䣬
	*p = 20;        //��Ӹ�ֵ������ı� a �е�ֵ����Ϊ����Ĳ���һ���ڴ�ռ�
	cout << "const a is: " << a << "\n";     // �����10
	cout << "point p is: " << *p << endl;    // �����20

	const int* const q = &a;	//q��һ��ָ����int�ĳ���ָ��

	//const_castֻ��ǿ��ת��ָ������ָ����߳������ã�����ֱ��ת���������ͱ���
	int* qq = const_cast<int*>(q);
	*qq = 20;
	cout << "const a is: " << a << "\n";     // �����10
	cout << "point qq is: " << *qq << endl;

	//reinterpret_cast���Խ�һ��ָ��ת��Ϊһ��int���ͣ���֮��ɣ�Ҳ����ת�����õ�int
	long long iqq = reinterpret_cast<long long>(qq);
	cout << "point qq value is: " << qq << endl;
	cout << "int iqq is: " << iqq << endl;
	int* newqq = reinterpret_cast<int*>(iqq);
	cout << "point newqq is: " << *newqq << endl;

     Base base("aaa");
     Derived de("xxx", 111);
     Base * pb = &de;
     if (Derived* pd = dynamic_cast<Derived*>(pb))
     {
        pd->print_ival();
     }
     else
     {
         //ת��ʧ�ܷ��ؿ�ָ��
		 cout << "type error..." << endl;
	 }

     //////////////////////////////////////////////////////////////

     //const���κ�������ֵ���������������ͣ���û��const��һ��
     //�������Զ������ͻ�������ָ��,�򷵻صľ��ǳ���
     int aa = add(10, 11);
     aa++;
     int* c = new int(0);
     //int* bb = sub(10, 5, c);
     const int *bb = sub(10, 5, c);

     //auto ���Զ���const, decltype��������const
     auto aaa = a;
     aaa = 1;
     decltype(a) bbb = 0;
     //bbb = 1;

     const int* const contptr = &a;
     auto aaaa = contptr;
     decltype(contptr) bbbb = &a;

     //auto�����Եײ�const
    // (*aaaa)++;
     aaaa = &b;
    // (*bbbb)++;
     //bbbb = &b;

     //ʹ��auto�ؼ��ֽ��������Ƶ�ʱ�������ʼ�����ʽ���������ͣ���������ȥ�����ã�������ʾ����
     //decltype ��ᱣ����������
     int i = 10;
     int& ri = i;
     auto ii = ri;
     ii = 11;
     cout << "i: " << i << "  ri: " << ri << "  ii: " << ii << endl;
     auto& iii = ri;
     iii = 12;
     cout << "i: " << i << "  ri: " << ri << "  iii: " << iii << endl;
     decltype(ri) iiii = ri;
     iiii = 13;
     cout << "i: " << i << "  ri: " << ri << "  iiii: " << iiii << endl;

     //�����������ͣ�auto�ؼ��ֻ��Ƶ�Ϊָ�����ͣ����Ǳ�����Ϊ���ã�decltype�򲻻�
	 int num[10];
	 auto numauto = num;
	 cout << typeid(numauto).name() << endl;   // �����int *

	 auto& numr = num;
	 cout << typeid(numr).name() << endl;   // �����int [10]

     decltype(num) numc = {0};

     //�Խ����ò�����auto�ƶϳ�ԭ�����ͣ�decltype�ƶϳ�����,���ñ����ʼ��
     int* ptrint = &iii;
     auto m = *ptrint;
     m++;
     cout << "ptrint: " << *ptrint << "  m: " << m << endl;
     //decltype(*ptrint) n;

     //auto��ִ�У�decltype����ִ��
     auto n = func();
     decltype(func()) o = 1;
     //decltype(func)�Ǻ������ͣ���*���Ǻ���ָ�����ͣ���ָ��lambda���ʽ
     decltype(func)* oo = []() { return 1; };

	getchar();
	return 0;
}