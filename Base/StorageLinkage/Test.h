#ifndef TEST_H
#define TEST_H

//定义在头文件内的const变量,包含头文件相当于在本文件内再次定义了一遍,存在两个const变量
//由于const是默认static和不变的常量,所以这么用也没问题
const int iConstInH = 100;

//添加了extern声明,包含这个头文件的文件也会有一个具有外部链接的const变量符号,重定义
//extern const int iConstExternInH = 100;
#endif
