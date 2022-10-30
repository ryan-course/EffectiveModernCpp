/*
	模板元编程

	SFINAE (Substitution failure is not an error) 替换失败并非错误
	是指C++语言在模板参数匹配失败时不认为这是一个编译错误

	- std::enable_if: 在std::enable_if指定的条件满足时模板才启用
	- std::is_same: 确定两个对象类型是否相同
	- std::decay: std::decay<T>::value与T是相同的，只不过会移除引用和cv限定符（cv-qualifiers，即const或volatile标识符）的修饰
					  还可以将数组或者函数退化成指针
   - std::is_base_of: 判断一个类型是否继承自另一个类型, 如果std::is_base_of<T1, T2>是true就表示T2派生自T1
						类型也可被认为是从他们自己派生，所以std::is_base_of<T, T>::value总是true
*/
#include <iostream>
using namespace std;

class Person
{
public:
	//控制Person完美转发构造函数的启用条件，只有当T在消除引用和cv限定符之后，并且既不是Person又不是Person的派生类时，才满足条件
	template <
		 typename T,
		 typename = typename std::enable_if<
			  !std::is_same<Person,
								 typename std::decay<T>::type>::value>::type>
	explicit Person(T &&n);  //完美转发构造函数
};

int main()
{

	return 0;
}

// 编译:命令
// g++ 'item_24_T&&.cpp' -o main; ./main