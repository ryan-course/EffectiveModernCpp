# EffectiveModernCpp

# C++标准术语

## RAII (Resource Acquisition Is Initialization) 资源获得即初始化
RAII对象 （ RAII objects ），从 RAII类 中实例化。（RAII全称为 “Resource Acquisition Is Initialization”（资源获得即初始化），尽管技术关键点在析构上而不是实例化上）。RAII类在标准库中很常见。比如STL容器（每个容器析构函数都销毁容器中的内容物并释放内存），标准智能指针（ Item18 - 20 解释了，std::uniqu_ptr的析构函数调用他指向的对象的删除器，std::shared_ptr和std::weak_ptr的析构函数递减引用计数），std::fstream对象（它们的析构函数关闭对应的文件）等。

## Pimpl（pointer to implementation）惯用法
将类数据成员替换成一个指向包含具体实现的类（或结构体）的指针，并将放在主类（primary class）的数据成员们移动到实现类（implementation class）去，而这些数据成员的访问将通过指针间接访问。

## RVO（return value optimization）返回值优化
C++标准会在分配给函数返回值的内存中直接构造对象
编译器可能会在按值返回的函数中消除对局部对象的拷贝（或者移动），如果满足
(1) 局部对象与函数返回值的类型相同；
(2) 局部对象就是要返回的东西。(返回局部对象的引用不满足RVO的第二个条件)
(3) 形参们没资格参与函数返回值的拷贝消除，但是如果作为返回值的话编译器会将其视作右值。

```cpp
Widget makeWidget()                 //makeWidget的“拷贝”版本
{
    Widget w;                       //局部对象
    …                               //配置w
    return w;                       //“拷贝”w到返回值中
}
```
**如果局部对象可以被返回值优化消除，就绝不使用std::move或者std::forward。**

## SFINAE (Substitution failure is not an error) 替换失败并非错误
是指C++语言在模板参数匹配失败时不认为这是一个编译错误

## TMP（template metaprogramming）模板元编程
如果想成为一个高效C++程序员，你需要至少熟悉C++在这方面的基本知识

可用于 取模板类型参数然后基于它创建另一种类型的. 
编写模板启用的条件

### type traits（类型特性）
C++11在type traits（类型特性）中给了你一系列工具去实现类型转换，如果要使用这些模板请包含头文件<type_traits>
- ==C++11的type traits是通过在struct内嵌套`typedef`来实现的== 	`typedef 类型 别名`
- ==C++14的type traits是通过在struct内嵌套`using`别名声明来实现的==	`using 别名 = 类型`

```cpp
#include <type_traits>

std::remove_const<T>::type          //C++11: const T → T 
std::remove_const_t<T>              //C++14 等价形式

std::remove_reference<T>::type      //C++11: T&/T&& → T 
std::remove_reference_t<T>          //C++14 等价形式

std::add_lvalue_reference<T>::type  //C++11: T → T& 
std::add_lvalue_reference_t<T>      //C++14 等价形式

std::enable_if<condition>::type> 	//在std::enable_if指定的条件满足时模板才启用

std::is_same<Person, T>::value 		//确定两个对象类型是否相同

std::decay<T>::value 					//std::decay<T>::value与T是相同的，只不过会移除引用和cv限定符（cv-qualifiers，即const或volatile标识符）的修饰
					  							//还可以将数组或者函数退化成指针

std::is_base_of<T1, T2>					//判断一个类型是否继承自另一个类型, 如果std::is_base_of<T1, T2>是true就表示T2派生自T1
												//类型也可被认为是从他们自己派生，所以std::is_base_of<T, T>::value总是true

std::is_constructible<T1, T2>			//确定一个类型T1的对象是否可以用另一个不同类型T2（或多个类型）的对象（或多个对象）来构造
```

## cv限定符（cv-qualifiers，即const或volatile标识符）

## 重载规则

重载规则规定当模板实例化函数和非模板函数（或者称为“正常”函数）匹配优先级相当时，优先使用“正常”函数