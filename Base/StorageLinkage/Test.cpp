#include "Test.h"

//����int����,�ⲿ��������
extern int iExtern = 10;
//������ȫ��,����extern�Ļ�,��ȫ����������Ҳ�ǿɼ���
int iGlobal = 1;
//const��������extern����,Ĭ����static��,ֻ�ڱ��ļ��ڿ���
const int iConst = 100;
extern const int iConstExtern = 100;

static int iStaticGlobal = 16;

//������������ռ�������,�����ļ���ֻҪ�����������ռ���ı���,Ҳ����ͨ�������ռ���õķ�ʽ���ñ���
namespace TestLinkage
{
	int iNameSpace = 11;
	extern auto iExternNameSpace = 12;
	
	//static��̬����,�ڲ�����
	static int iStaticNameSpace = 10;
}

void func()
{
	int iInternal = 13;

	//�˴����ܶ����ⲿ����,�ᵱ����������,���������ٶ������
	//extern int iExternInFunc = 14;
}