/*
	std::shared_ptr为有共享所有权的任意资源提供一种自动垃圾回收的便捷方式。
	较之于std::unique_ptr,std::shared_ptr对象通常大两倍,包含一个指向对象的指针和一个指向控制块的指针
	控制块内包含引用计数,弱引用计数,自定义删除器和自定义分配器
	引用计数的开销: 需要原子性的引用计数修改操作。

	当你想在成员函数中使用std::shared_ptr指向this所指对象时,要使用`shared_from_this`,它不会创建多余的控制块

	避免从原始指针变量上创建std::shared_ptr, 如果使用同一个原始指针创建两个shared_ptr,会出错
	std::shared_ptr不能处理数组
*/
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

std::vector<std::shared_ptr<Widget>> processedWidgets;

class Widget: public std::enable_shared_from_this<Widget> {
public:
    void process();
};

void Widget::process()
{
    //和之前一样，处理Widget
    //把指向当前对象的std::shared_ptr加入processedWidgets
    processedWidgets.emplace_back(shared_from_this());
}


int main()
{
	
	return 0;
}


// 编译:命令
// g++ item_18_unique_ptr.cpp -o main