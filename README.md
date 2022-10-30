# EffectiveModernCpp
---

# C++标准术语

- 移动语义（ move semantics ）
- 完美转发（ perfect forwarding ）
  - 不仅转发对象，我们还转发显著的特征：它们的类型，是左值还是右值，是const还是volatile
- 位域
  - 最低有效位（least significant bit，lsb）
  - 最高有效位（most significant bit，msb）

## 手法

### RAII (Resource Acquisition Is Initialization) 资源获得即初始化

RAII对象 （ RAII objects ），从 RAII类 中实例化。（RAII全称为 "Resource Acquisition Is Initialization"（资源获得即初始化），尽管技术关键点在析构上而不是实例化上）。RAII类在标准库中很常见。比如STL容器（每个容器析构函数都销毁容器中的内容物并释放内存），标准智能指针（ Item18 - 20 解释了，std::uniqu_ptr的析构函数调用他指向的对象的删除器，std::shared_ptr和std::weak_ptr的析构函数递减引用计数），std::fstream对象（它们的析构函数关闭对应的文件）等。

### Pimpl（pointer to implementation）惯用法

将类数据成员替换成一个指向包含具体实现的类（或结构体）的指针，并将放在主类（primary class）的数据成员们移动到实现类（implementation class）去，而这些数据成员的访问将通过指针间接访问。

## 模板

### TMP（template metaprogramming）模板元编程

如果想成为一个高效C++程序员，你需要至少熟悉C++在这方面的基本知识

可用于:
- 取模板类型参数然后基于它创建另一种类型的. 
- 编写模板启用的条件

### SFINAE (Substitution failure is not an error) 替换失败并非错误

是指C++语言在模板参数匹配失败时不认为这是一个编译错误

### Type Traits（类型特性）

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

std::enable_if<condition>::type>  //在std::enable_if指定的条件满足时模板才启用

std::is_same<Person, T>::value   //确定两个对象类型是否相同

std::decay<T>::value      //std::decay<T>::value与T是相同的，只不过会移除引用和cv限定符（cv-qualifiers，即const或volatile标识符）的修饰
              //还可以将数组或者函数退化成指针

std::is_base_of<T1, T2>     //判断一个类型是否继承自另一个类型, 如果std::is_base_of<T1, T2>是true就表示T2派生自T1
            //类型也可被认为是从他们自己派生，所以std::is_base_of<T, T>::value总是true

std::is_constructible<T1, T2>   //确定一个类型T1的对象是否可以用另一个不同类型T2（或多个类型）的对象（或多个对象）来构造
```

### Reference Collapsing（引用折叠）

在C++中手写引用的引用是非法的, 但是编译器会在特定的上下文中产生, 最终会推导为单个引用
**如果任一引用为左值引用，则结果为左值引用。否则（即，如果引用都是右值引用），结果为右值引用。**

引用折叠发生在四种情况下：
- 模板实例化，
- auto类型推导，
- typedef与别名声明的创建和使用，
- decltype

### 重载规则

重载规则规定当模板实例化函数和非模板函数（或者称为"正常"函数）匹配优先级相当时，优先使用"正常"函数

### cv-qualifiers（cv限定符，即const或volatile标识符）

## 编译器自动做的优化

### RVO（return value optimization）返回值优化

C++标准会在分配给函数返回值的内存中直接构造对象
编译器可能会在按值返回的函数中消除对局部对象的拷贝（或者移动），如果满足
(1) 局部对象与函数返回值的类型相同；
(2) 局部对象就是要返回的东西。(返回局部对象的引用不满足RVO的第二个条件)
(3) 形参们没资格参与函数返回值的拷贝消除，但是如果作为返回值的话编译器会将其视作右值。

```cpp
Widget makeWidget()                 //makeWidget的"拷贝"版本
{
    Widget w;                       //局部对象
    …                               //配置w
    return w;                       //"拷贝"w到返回值中
}
```
**如果局部对象可以被返回值优化消除，就绝不使用std::move或者std::forward。**

### SSO（small string optimization）小字符串优化

“小”字符串（比如长度小于15个字符的）存储在了std::string的缓冲区中，并没有存储在堆内存。
SSO的动机是大量证据表明，短字符串是大量应用使用的习惯。使用内存缓冲区存储而不分配堆内存空间，是为了更好的效率。

### const propagation（常量传播）

无需在类中定义整型static const数据成员；声明就可以了

```cpp
class Widget {
public:
    static const std::size_t MinVals = 28;  //MinVal的声明
    …
};
…                                           //没有MinVals定义

std::vector<int> widgetData;
widgetData.reserve(Widget::MinVals);        //使用MinVals
```
