/*
	Pimpl（pointer to implementation）惯用法
    将类数据成员替换成一个指向包含具体实现的类（或结构体）的指针，并将放在主类（primary class）的数据成员们移动到实现类（implementation class）去，而这些数据成员的访问将通过指针间接访问。

    好处是头文件中依赖的其它文件变少,加速编译
*/

#include <iostream>
using namespace std;

class Widget                        //仍然在“widget.h”中
{
public:
    Widget();
    ~Widget();                      //析构函数在后面会分析

private:
    struct Impl;                    //声明一个 实现结构体
    Impl *pImpl;                    //以及指向它的指针
};
