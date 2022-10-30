/*
	标准库并发组件（任务tasks，期望futures，线程threads，互斥mutexes，条件变量condition variables，原子对象atomic objects等）

	- std::thread API不能直接访问异步执行的结果，如果执行函数有异常抛出，代码会终止执行。
	- std::async 基于任务的设计为开发者避免了手动线程管理的痛苦，并且自然提供了一种获取异步执行程序的结果（即返回值或者异常）的方式。

	async的启动策略:
	- 默认的策略: std::launch::async | std::launch::deferred, 允许f异步或者同步执行(机器资源超额或者线程耗尽的条件，此时任务推迟执行才最有可能发生)
	- std::launch::async: 必须异步执行，即在不同的线程
	- std::launch::deferred: 仅当在std::async返回的future上调用get或者wait时才执行. 惰性求值
*/
#include <iostream>
#include <thread>
#include <future>
using namespace std;

int doAsyncWork()
{
	cout << "doAsyncWork" << endl;
	return 0;
}

using namespace std::literals; //为了使用C++14中的时间段后缀；参见条款34

void f() // f休眠1秒，然后返回
{
	std::this_thread::sleep_for(1s);
	cout << "f" << endl;
}

void wait_for();

int main()
{
	//基于线程（thread-based）的方式
	std::thread t(doAsyncWork);
	t.join(); //等待直到执行完成

	//基于任务（task-based）的策略
	auto fut = std::async(doAsyncWork); //“fut”表示“future”
	fut.get();									//等待直到执行完成, 获取返回值
	cout << "get future return" << endl;

	//使用async或者deferred运行f (默认的策略也是这样)
	auto fut2 = std::async(std::launch::async | std::launch::deferred, 
								  doAsyncWork);

	wait_for();

	return 0;
}

void wait_for()
{
	// auto fut  = std::async(std::launch::async, f);   //指定异步启动f的执行
	auto fut = std::async(f); //可能异步或者(同步)延迟执行

	if (fut.wait_for(0s) == //如果task是deferred（被延迟）状态
		 std::future_status::deferred)
	{
		cout << "future_status is deferred" << endl;
		fut.get();                                   //在fut上调用wait或get来异步调用f
	}
	else
	{											// task没有deferred（被延迟）
		while (fut.wait_for(100ms) != //不可能无限循环（假设f完成）
				 std::future_status::ready)
		{
			//…                               //task没deferred（被延迟），也没ready（已准备）
			//做并行工作直到已准备
			cout << "done other .." << endl;
		}
		//…                                   //fut是ready（已准备）状态
		cout << "future_status is ready" << endl;
	}
}

// 编译:命令
// g++ item_35_async.cpp -lpthread -o main; ./main