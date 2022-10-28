/*
	只要你在派生类声明想要重写基类虚函数的函数，就加上`override`

	`成员函数的引用限定符`是C++11的新特性，它可以限定成员函数只能用于左值或者右值
*/
#include <iostream>
using namespace std;

class Widget {
public:
    void doWork() & {cout<<"call by left value"<<endl;}    //只有*this为左值的时候才能被调用
    void doWork() && {cout<<"call by right value"<<endl;}   //只有*this为右值的时候才能被调用
}; 

Widget makeWidget() {return Widget();}    //工厂函数（返回右值）
Widget w;               //普通对象（左值）

int main()
{
	w.doWork();             //调用被左值引用限定修饰的Widget::doWork版本
                        	//（即Widget::doWork &）
	makeWidget().doWork();  //调用被右值引用限定修饰的Widget::doWork版本
                        	//（即Widget::doWork &&）
	return 0;
}

class Base {
public:
    virtual void mf1() const;
    virtual void mf2(int x);
    virtual void mf3() &;
    virtual void mf4() const;
};

class Derived: public Base {
public:
    virtual void mf1() const override;
    virtual void mf2(int x) override;
    virtual void mf3() & override;
    void mf4() const override;          //可以添加virtual，但不是必要
}; 


// 编译:命令
// g++ item_12_right_value.cpp -o main