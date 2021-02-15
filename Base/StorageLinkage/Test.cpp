#include "Test.h"

//定义int变量,外部链接属性
extern int iExtern = 10;
//作用域全局,不加extern的话,在全局作用域内也是可见的
int iGlobal = 1;
//const变量不加extern声明,默认是static的,只在本文件内可用
const int iConst = 100;
extern const int iConstExtern = 100;

static int iStaticGlobal = 16;

//如果加了命名空间作用域,其他文件里只要声明了命名空间里的变量,也可以通过命名空间调用的方式调用变量
namespace TestLinkage
{
	int iNameSpace = 11;
	extern auto iExternNameSpace = 12;
	
	//static静态链接,内部链接
	static int iStaticNameSpace = 10;
}

void func()
{
	int iInternal = 13;

	//此处不能定义外部变量,会当作声明处理,导致声明再定义错误
	//extern int iExternInFunc = 14;
}