#include "widget.h" //以下代码均在实现文件“widget.cpp”里
#include <vector>
#include <string>

struct Widget::Impl
{                     //含有之前在Widget中的数据成员的
    std::string name; // Widget::Impl类型的定义
    std::vector<double> data;
};

Widget::Widget() //为此Widget对象分配数据成员
    : pImpl(std::make_unique<Impl>())
{
}

Widget::~Widget() = default; //析构函数的定义

Widget::Widget(const Widget &rhs) //拷贝构造函数
    : pImpl(std::make_unique<Impl>(*rhs.pImpl))
{
}

Widget &Widget::operator=(const Widget &rhs) //拷贝operator=
{
    *pImpl = *rhs.pImpl;
    return *this;
}

Widget::Widget(Widget &&rhs) = default; //这里定义
Widget &Widget::operator=(Widget &&rhs) = default;