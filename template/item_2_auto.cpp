/*
	Item_2: auto
	在auto类型推导时，对于non-reference类型说明符，数组名或者函数名会退化为指针

	auto类型推导和模板类型推导的真正区别在于，auto类型推导假定花括号表示std::initializer_list而模板类型推导不会这样
*/

#include <iostream>
#include <array>
#include <vector>
using namespace std;

//C++14允许auto用于函数返回值并会被推导
auto createInitList()
{
   //  return { 1, 2, 3 };         //错误！不能推导{ 1, 2, 3 }的类型
	return 1;
}

void someFunc(int, double){} // someFunc是一个函数，类型为void(int, double)

int main()
{
	// auto x2;                        //错误！必须要初始化

	auto index = static_cast<int>( 2.7 * 10);//显式类型初始器惯用法强制auto推导出你想要的结果

	const char name[] = "R. N. Briggs"; // name的类型是const char[13]
	auto arr1 = name;	 // arr1的类型是const char*
	auto &arr2 = name; // arr2的类型是const char (&)[13]

	//-------------
	auto func1 = someFunc;	// func1的类型是void (*)(int, double)
	auto &func2 = someFunc; // func2的类型是void (&)(int, double)

	//--------------
	auto x1 = 27;                   //类型是int，值是27
	auto x2(27);                    //同上

	auto x3 = { 27 };               //类型是std::initializer_list<int>，值是{ 27 }
	auto x4{ 27 };                  //同上
	// auto x5 = { 1, 2, 3.0 };        //错误！无法推导std::initializer_list<T>中的T

	//-------------
	std::cout << createInitList() << std::endl;

	//C++14的lambda函数也允许在形参声明中使用auto
	std::vector<int> v;
	auto resetV = 
		[&v](const auto& newValue){ v = newValue; };        //C++14

	// resetV({ 1, 2, 3 });            //错误！不能推导{ 1, 2, 3 }的类型
	resetV(vector<int>{1, 2, 3});

	//-------------
	std::cout << typeid(x1).name() << std::endl; //输出 'i', 表示 int

	//-------------
	// const int i = 0;                //decltype(i)是const int

	// bool f(const Widget& w);        //decltype(w)是const Widget&
	// 										//decltype(f)是bool(const Widget&)

	// struct Point{
	// 	int x,y;                    //decltype(Point::x)是int
	// };                              //decltype(Point::y)是int

	// Widget w;                       //decltype(w)是Widget

	// if (f(w))…                      //decltype(f(w))是bool

	// template<typename T>            //std::vector的简化版本
	// class vector{
	// public:
	// 	…
	// 	T& operator[](std::size_t index);
	// 	…
	// };

	// vector<int> v;                  //decltype(v)是vector<int>
	// …
	// if (v[0] == 0)…                 //decltype(v[0])是int&

	return 0;
}

// #include <boost/type_index.hpp>
// template<typename T>
// void f(const T& param)
// {
//     using std::cout;
//     using boost::typeindex::type_id_with_cvr;

//     //显示T
//     cout << "T =     "
//          << type_id_with_cvr<T>().pretty_name()
//          << '\n';
    
//     //显示param类型
//     cout << "param = "
//          << type_id_with_cvr<decltype(param)>().pretty_name()
//          << '\n';
// }


// 编译:命令
// g++ item_2_auto.cpp -o main
