/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/15
 *
 * \brief const volatile auto ,类型转换等相关demo
 */

#include <iostream>

using namespace std;

//const修饰函数返回值，若返回内置类型，有没有const都一样
//若返回自定义类型或者引用指针,则返回的就是常量
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
         cout << "仅输出ival的值：" << ival << endl;
     }
 private:
     int ival;
 };

int main()
{
	const int a = 10; // a 定义为一个常量
    const int b = 11;

	int* p = nullptr;
	p = (int*)&a;  //此处取a 的地址，但C++会单独分配一个新的内存空间，
	*p = 20;        //间接赋值，不会改变 a 中的值，因为保存的不是一个内存空间
	cout << "const a is: " << a << "\n";     // 输出：10
	cout << "point p is: " << *p << endl;    // 输出：20

	const int* const q = &a;	//q是一个指向常量int的常量指针

	//const_cast只能强制转换指向常量的指针或者常量引用，不能直接转换常量类型变量
	int* qq = const_cast<int*>(q);
	*qq = 20;
	cout << "const a is: " << a << "\n";     // 输出：10
	cout << "point qq is: " << *qq << endl;

	//reinterpret_cast可以将一个指针转化为一个int类型，反之亦可，也可以转换引用到int
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
         //转换失败返回空指针
		 cout << "type error..." << endl;
	 }

     //////////////////////////////////////////////////////////////

     //const修饰函数返回值，若返回内置类型，有没有const都一样
     //若返回自定义类型或者引用指针,则返回的就是常量
     int aa = add(10, 11);
     aa++;
     int* c = new int(0);
     //int* bb = sub(10, 5, c);
     const int *bb = sub(10, 5, c);

     //auto 忽略顶层const, decltype保留顶层const
     auto aaa = a;
     aaa = 1;
     decltype(a) bbb = 0;
     //bbb = 1;

     const int* const contptr = &a;
     auto aaaa = contptr;
     decltype(contptr) bbbb = &a;

     //auto不忽略底层const
    // (*aaaa)++;
     aaaa = &b;
    // (*bbbb)++;
     //bbbb = &b;

     //使用auto关键字进行类型推导时，如果初始化表达式是引用类型，编译器会去除引用，除非显示声明
     //decltype 则会保留引用类型
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

     //对于数组类型，auto关键字会推导为指针类型，除非被声明为引用，decltype则不会
	 int num[10];
	 auto numauto = num;
	 cout << typeid(numauto).name() << endl;   // 输出：int *

	 auto& numr = num;
	 cout << typeid(numr).name() << endl;   // 输出：int [10]

     decltype(num) numc = {0};

     //对解引用操作，auto推断出原有类型，decltype推断出引用,引用必须初始化
     int* ptrint = &iii;
     auto m = *ptrint;
     m++;
     cout << "ptrint: " << *ptrint << "  m: " << m << endl;
     //decltype(*ptrint) n;

     //auto会执行，decltype不会执行
     auto n = func();
     decltype(func()) o = 1;
     //decltype(func)是函数类型，加*就是函数指针类型，可指向lambda表达式
     decltype(func)* oo = []() { return 1; };

	getchar();
	return 0;
}