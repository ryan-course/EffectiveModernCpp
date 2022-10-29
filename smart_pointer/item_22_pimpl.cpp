#include "item_22_pimpl.h"             //以下代码均在实现文件“widget.cpp”里
#include <memory>
#include <vector>
#include <string>

struct Widget::Impl {           //含有之前在Widget中的数据成员的
    std::string name;           //Widget::Impl类型的定义
    std::vector<double> data;
};

Widget::Widget()                //为此Widget对象分配数据成员
: pImpl(new Impl)
{}

Widget::~Widget()               //销毁数据成员
{ delete pImpl; }
