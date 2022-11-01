/*
	对于简单的事件通信，基于条件变量的设计需要一个多余的互斥锁，对检测和反应任务的相对进度有约束，并且需要反应任务来验证事件是否已发生。
	基于flag的设计避免的上一条的问题，但是是基于轮询，而不是阻塞。
*/
#include <iostream>
#include <condition_variable>
#include <mutex>
using namespace std;

int main()
{
	//检测任务代码
	std::condition_variable cv;             //跟之前一样
	std::mutex m;
	bool flag(false);                       //不是std::atomic
	// …                                       //检测某个事件
	{
		std::lock_guard<std::mutex> g(m);   //通过g的构造函数锁住m
		flag = true;                        //通知反应任务（第1部分）
	}                                       //通过g的析构函数解锁m
	cv.notify_one();                        //通知反应任务（第2部分）


	//反应任务代码
	// …                                       //准备作出反应
	{                                       //跟之前一样
		std::unique_lock<std::mutex> lk(m); //跟之前一样
		cv.wait(lk, [] { return flag; });   //使用lambda来避免虚假唤醒
		//  …                                   //对事件作出反应（m被锁定）
	}
	// …                                       //继续反应动作（m现在解锁）


	return 0;
}

// 编译:命令
// g++ item_40_atomic.cpp -o main