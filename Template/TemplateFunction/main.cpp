/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/2/23
 *
 * \brief ģ�庯�����demo
 *  \content:
 * 1��ģ�庯����������ʽģ��ʵ�ε��ã�2����ʽ����ʽʵ������3��ģ�庯��ȫ�ػ������أ�
 * 4����ģ���������ֵȷ����auto��std::common_type����5��Ĭ��ģ������������βκͷ������βΣ�
 * 5��ģ�庯���İ��ػ�
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//ģ�庯��*****************************************//
//��������auto������ʵ�����ȷ����������
template<typename T, typename U>
auto Max(T t, U u)
{
	cout << "Max<T, U>" << endl;
	return t > u ? t : u;
}

//��ʽʵ����
template auto Max<float, float>(float, float);

//ģ�庯��ȫ�ػ�
template<>
auto Max<int, double>(int a, double b)
{
	cout << "Max<int, double>" << endl;
	return a > b ? a : b;
}

//ģ�庯������
int Max(int a, int b)
{
	cout << "Max(int, int)" << endl;
	return a > b ? a : b;
}

template<typename T, typename U>
std::common_type_t<T, U> Min(T t, U u)
{
	return t > u ? u : t;
}

//Ĭ��ģ������������βκͷ������βΣ�****************************************//
//�����βε�Ĭ��ֵ
//template<typename T, typename Ts>//û�и�Ts��Ĭ��ֵ, ����print(1)��������
template<typename T, typename Ts = ostream>
void print(T input, Ts& os = cout) {
	os << input << endl;
}

//������ģ����������ƺ�Ĭ��ֵ
//������Ա���ɹ�
// template<class T, int a = 11>  void h(T b) {} 
//�����޷�����ɹ�����Ϊh(T b, int a = 11)�е�a������ģ�����a
//template<class T, int a = 11> void h(T b, int a = 11) {}
//������Ա���ɹ�
template<class T, int a = 11> void h(T b, int c = 11) {}

//ģ�庯��ƫ�ػ�(ʹ��conceptʵ��)****************************************//
template<typename T, typename U>
void PrintNew(T t, U u)
{
	cout << "PrintNew<T, U> " << t << " " << u << endl;
}

template<typename T, typename U>
requires std::integral<U>	//Ҫ��U��int����
void PrintNew(T t, U u)
{
	cout << "PrintNew<T, int> " << t << " " << u << endl;
}


int main()
{
	//ģ�庯��*****************************************//
	cout << Max(1.1f, 2.2f) << endl;

	//��ʽʵ����
	//��ʽ����
	cout << Max(1, 1.1f) << endl;

	//��ʽģ��ʵ�ε���
	cout << Max<string, string>("abc", "def") << endl;

	//ȫ�ػ�
	cout << Max(1, 2.2) << endl;
	cout << Max<int, double>(5.1, 2) << endl;

	//���أ������;���һ�£����ȵ�����ͨ����
	cout << Max(1, 2) << endl;
	//������ģ��ƥ����ã����ȵ���ģ�庯��
	cout << Max(1, 2l) << endl;
	//��ǿ�Ƶ���ģ�庯��
	cout << Max<>(1, 2) << endl;

	//std::common_type
	cout << Min(1, 10.0f) << endl;

	cout << "****************************" << endl;

	//Ĭ��ģ������������βκͷ������βΣ�****************************************//
	//�����βε�Ĭ��ֵ
	print(1);

	//������ģ����������ƺ�Ĭ��ֵ
	h(1);
	h<int, 10>(100);//��ʽʵ����ָ���������β�ֵ

	cout << "****************************" << endl;

	//ģ�庯��ƫ�ػ�(ʹ��conceptʵ��)****************************************//
	PrintNew(1, 1.1);
	PrintNew(1, 2);

	system("pause");
	return 0;
}

