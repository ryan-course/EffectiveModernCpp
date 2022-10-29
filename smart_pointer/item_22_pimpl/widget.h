/*
	Pimpl（pointer to implementation）惯用法
    将类数据成员替换成一个指向包含具体实现的类（或结构体）的指针，并将放在主类（primary class）的数据成员们移动到实现类（implementation class）去，而这些数据成员的访问将通过指针间接访问。

    - 好处是头文件中依赖的其它文件变少,加速编译
    - 对于std::unique_ptr类型的pImpl指针，需要在头文件的类里声明特殊的成员函数，但是在实现文件里面来实现他们。即使是编译器自动生成的代码可以工作，也要这么做。
        - td::shared_ptr不需要手动定义,但会生成更大的运行时数据结构(控制块)和稍微慢点的代码(原子操作引用计数)

    注意:使用unique_ptr指向未完成类型的话,类需要显示定义析构函数
    声明一个类Widget的析构函数会阻止编译器生成移动操作，所以如果你想要支持移动操作，你必须自己声明相关的函数
*/

#include <iostream>
#include <memory>
using namespace std;

class Widget                        //仍然在“widget.h”中
{
public:
    Widget();
    ~Widget();

    //拷贝操作
    Widget(const Widget& rhs);          //只有声明
    Widget& operator=(const Widget& rhs);
    
    //移动操作
    Widget(Widget&& rhs);               //只有声明
    Widget& operator=(Widget&& rhs);

private:
    struct Impl;                    //声明一个 实现结构体,是一个未完成类型
    std::unique_ptr<Impl> pImpl;    //以及指向它的指针
};
