/*
	std::unique_ptr 只可移动(移动后,源指针被设为null),不能拷贝
	默认情况下，资源析构通过对std::unique_ptr里原始指针调用delete来实现
	一种用于单个对象（std::unique_ptr<T>），一种用于数组（std::unique_ptr<T[]>）

	得通过`reset`来让unique_ptr接管通过`new`创建的对象的所有权
	将std::unique_ptr转化为std::shared_ptr非常简单, 
*/
#include <iostream>
#include <memory>
using namespace std;

class Investment {
public:
    virtual ~Investment();          //关键设计部分！
};

Investment::~Investment(){}


// template<typename... Ts>
// auto makeInvestment(Ts&&... params)                 //C++14
// {
//     auto delInvmt = [](Investment* pInvestment)     //现在在
//                     {                               //makeInvestment里
//                         makeLogEntry(pInvestment);
//                         delete pInvestment; 
//                     };

//     std::unique_ptr<Investment, decltype(delInvmt)> //自定义删除器
//         pInv(nullptr, delInvmt);
//    //  if ( … )                                        //同之前一样
//     {
//         pInv.reset(new Stock(std::forward<Ts>(params)...));	//接管通过`new`创建的对象的所有权
//     }
//    //  else if ( … )                                   //同之前一样
//     {     
//         pInv.reset(new Bond(std::forward<Ts>(params)...));   
//     }   
//    //  else if ( … )                                   //同之前一样
//     {     
//         pInv.reset(new RealEstate(std::forward<Ts>(params)...));   
//     }   
//     return pInv;                                    //同之前一样
// }


int main()
{
	auto p = std::make_unique<Investment>(); // with make func
	auto p1(std::make_unique<Investment>()); // with make func
	std::unique_ptr<Investment> upw2(new Investment); // with new, without make func

	std::unique_ptr<Investment> ptr;
	ptr.reset(new Investment());
	

	std::shared_ptr<Investment> sp = std::make_unique<Investment>();         //将std::unique_ptr 转为std::shared_ptr

	return 0;
}


// 编译:命令
// g++ item_18_unique_ptr.cpp -o main