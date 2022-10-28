/*
	Item_1: 模板类型推导
	在模板类型推导时，数组名或者函数名实参会退化为指针，除非它们被用于初始化引用
*/

#include <iostream>
#include <array>
using namespace std;

// 定义一个函数模板
template <typename T>
void TempFun(T& a)
{
    cout << a << endl;
}

//在编译期间返回一个数组大小的常量值（//数组形参没有名字，
//因为我们只关心数组的大小）
template<typename T, std::size_t N>                     
constexpr std::size_t arraySize(T (&)[N]) noexcept      //constexpr: 使结果在编译期间可用
{                                                       //noexcept: 使编译器生成更好的代码
    return N;                                           
}                                                       


int main()
{
    int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
    TempFun(keyVals);   // T被推导为const char[13]

	 std::cout << arraySize(keyVals) << std::endl;

	 std::array<int, arraySize(keyVals)> mappedVals;         //mappedVals的大小为7
	 std::cout << mappedVals.size() << std::endl;
	 
	 return 0;
}

// 编译:命令
// g++ item_1_constexpr.cpp -o main
// g++ -std=c++11 item_1.cpp -o main
