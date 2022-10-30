/*
	“T&&”是通用引用, 它既可以是右值引用，也可以是左值引用。这种引用在源码里看起来像右值引用（即“T&&”），但是它们可以表现得像是左值引用（即“T&”）
	'auto&&'的变量可以是通用引用,会发生类型推导，并且它们具有正确形式(T&&)
	存在类型推导的过程,是通用引用; 没有类型推导,则是右值引用
	把它叫做通用引用（universal references）。
*/
#include <iostream>
using namespace std;

class Widget
{
public:																			//成员函数的引用限定符
																					//  |
	void doWork() & { cout << "call by left value" << endl; }	//只有*this为左值的时候才能被调用
	void doWork() && { cout << "call by right value" << endl; } //只有*this为右值的时候才能被调用
};

template <typename T>
void f(T &&param); // param是一个**通用引用**

template <typename T>
void fr(const T &&param); // param是一个右值引用

template <typename T>
void foo(std::vector<T> &&param); //右值引用

void fn(Widget &&param); //右值引用

int main()
{
	Widget &&var1 = Widget(); //右值引用
	auto &&var2 = var1;		  //				**通用引用**

	Widget w;
	f(w); //传递给函数f一个左值；param的类型
			//将会是Widget&，也即左值引用

	f(std::move(w)); //传递给f一个右值；param的类型会是
						  // Widget&&，即右值引用

	//函数timeFuncInvocation可以对近乎任意（pretty much any）函数进行计时
	auto timeFuncInvocation =
		 [](auto &&func, auto &&...params) // C++14
	{
		// start timer;
		std::forward<decltype(func)>(func)( //对params调用func
			 std::forward<delctype(params)>(params)...);
		// stop timer and record elapsed time;
	};

	return 0;
}

//标准库中支持完美转发的make方法 (支持无限个参数)
// template<class T, class... Args>                //来自C++11标准
// shared_ptr<T> make_shared(Args&&... args);

// template<class T, class... Args>                //来自C++14标准
// unique_ptr<T> make_unique(Args&&... args);


// 编译:命令
// g++ 'item_24_T&&.cpp' -o main; ./main