/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/23
 *
 * \brief ģ�������demo
 *  \content:
 * 1��ģ���������2����ʽ����ʽʵ��������Ա����ʵ����ʱ��
 * 3��ģ�������Ԫ��������Ԫ�ࣨ����������ʽ����
 * 4��ģ�����ȫ�ػ������ػ������ػ�Ϊ��һ��ģ����
 * 5��deduced guides �ƶ�ָ������
 * 6��concept
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//ģ����*****************************************//

//��Ԫģ�庯������Ԫģ����*****************************************//
template<typename T, typename U>
class Pair;

template<typename T, typename U>
class A
{
public:
	void Test()
	{
		Pair<int, int> p;
		//����Pair<int,int>��private��Ա����, ���ʵ����Test,��������
		int a = p.first_;
	}
};

//�󶨵���Ԫģ�庯�����˴��������Ͷ��壬Ҫ�������Ͷ���
//template<typename T, typename U>
//class Pair;
//
//template<typename T, typename U>
//ostream& operator<< (ostream& os, const Pair<T, U>& pair)
//{
//	os << pair.first_ << " : " << pair.second_;
//	Pair<int, int> p(1, 2);
//	//������1��1�󶨵���Ԫģ�庯���������޷�����<int,int>���͵�private��Ա
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

	//��Զ�ķǰ󶨵���Ԫģ�庯������v��w���Ժ�T��U��ͬ��operator<< <string, int>������Pair<double, float>����Ԫ
	template<typename V, typename W>
	friend ostream& operator<< (ostream& os, const Pair<V, W>& pair);

	//һ��һ�İ󶨵���Ԫģ�庯������ʱoperator<< <string, int>ֻ����Pair<string,int>����Ԫ��ע��˴�����operator<<��Ҫ��<T, U>��˵���˴���Ԫģ�庯���Ѿ�ʵ����
	//friend ostream& operator<<<T, U> (ostream& os, const Pair<T, U>& pair);

	//��Զ�ķǰ���Ԫģ���࣬A������ǰ����
// 	template<typename T, typename U>
// 	friend class A;

	//һ��һ�İ󶨵���Ԫģ���� AҪ��ǰ����
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
	//�����Ƕ�Զ����Ԫģ�庯�������Է��ʴ����͵�private��Ա
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

//��ģ�����ʽʵ��������ʵ����������г�Ա����������������������ʽʵ����һ����ֻ�г�Ա��������ʱ��ʵ������Ա����
//�˴�����������Ϊ��Ԫģ������һһ��Ӧ��
//template class A<string, int>;

//�����Ƶ�ָ��,��Pair(const char*, double)�Ƶ�Ϊ Pair<string, int>����
Pair(const char*, double) -> Pair<string, int>;

//ģ�����ػ������ػ�*****************************************//
//ȫ�ػ�
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

//������Ա�����ݲ��ػ�

//���ػ�, Ҳ���԰��ػ�ΪT* ��T&����
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

//���ػ�Ϊ��һ��ģ����
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

//conceptԼ��*****************************************//
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
	//ģ����*****************************************//
	Pair<string, int> pair1;
	Pair<string, int> pair2("Age", 20);
	Pair<string, int> pair3 = pair2;
	pair1 = pair2;
	pair2.set_first("Grade");
	pair2.set_second(100);
	cout << pair1 << endl;
	cout << pair2 << endl;
	cout << pair3 << endl;

	//��ʽʵ����ֻ�����Ķ��壬��Ա������ûʵ����
	A<string, int> a;

	//���ģ��������ʽʵ������ģ����ĳ�Ա����ֻ�е���ʱ��ʵ����
	//ʵ������, ����A<string, int>�޷�����Pair<int,int>��private��Ա,��Ϊ��һ��һ�󶨵�ģ����Ԫ��
	//a.Test();

	//�����Ƶ�ָ��,��Pair(const char*, double)�Ƶ�Ϊ Pair<string, int>����, �����int����
	Pair pair4("test", 1.111);
	cout << pair4 << endl;

	cout << "****************************" << endl;

	//�ػ���Pair<double, double>����
	Pair<double, double> pair5(1.11, 2.22);
	Pair<double, double> pair6 = pair5;
	cout << pair5 << pair6 << endl;

	//���ػ���Pair<T, string>����
	Pair<double, string> pair7(1.11, "double");
	Pair<double, string> pair8 = pair7;
	cout << pair7 << pair8 << endl;

	//���ػ���Pair<T, vector<T> >����
	Pair<double, vector<double> > pair9(1.11, {2.2, 3.3});
	Pair<double, vector<double> > pair10 = pair9;
	vector<double> second = pair10.second();
	for (auto a : second)
	{
		cout << a << endl;
	}
	cout << "****************************" << endl;

	//concept�Ѿ�Լ����T�����������͵ģ�double���޷�ͨ������
	//Test<double> test;
	Test<int> test;
	Test<long> test;
	

	system("pause");
	return 0;
}