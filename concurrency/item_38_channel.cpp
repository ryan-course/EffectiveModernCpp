/*
	被调用者（通常是异步执行）将计算结果写入通信信道中（通常通过std::promise对象），调用者使用future读取结果
*/
#include <iostream>
#include <future>
using namespace std;

int main()
{

	return 0;
}

//-----------
//一个发送端, 一个接收端的channel实现
//-----------
std::promise<void> p;
void react(); //反应任务的函数
void detect() //检测任务的函数
{
	std::thread t([] //创建线程
					  {
								p.get_future().wait();    //挂起t直到future被置位
								react(); });
	// …                                   //这里，t在调用react前挂起
	p.set_value(); //解除挂起t（因此调用react）
	// …                                   //做其他工作
	t.join(); //使t不可结合（见条款37）
}

//-----------
//一个发送端, 多个接收端的channel实现
//-----------
std::promise<void> p; //跟之前一样
void detect()			 //现在针对多个反映线程
{
	auto sf = p.get_future().share(); // sf的类型是std::shared_future<void>
	std::vector<std::thread> vt;		 //反应线程容器
	for (int i = 0; i < threadsToRun; ++i)
	{
		vt.emplace_back([sf]
							 { sf.wait();    //在sf的局部副本上wait；
                              react(); }); // emplace_back见条款42
	}
	…						 //如果这个“…”抛出异常，detect挂起！
		 p.set_value(); //所有线程解除挂起
	… for (auto &t : vt)
	{				 //使所有线程不可结合；
		t.join(); //“auto&”见条款2
	}
}

// 编译:命令
// g++ item_40_atomic.cpp -o main