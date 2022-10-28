/*
	std::atomic 操作是使用特定的机器指令实现，这比锁的实现更高效
	std::atomic 使用的一致性模型: 顺序一致性（sequential consistency）
	std::atomic 不支持拷贝构造和拷贝赋值,所以拷贝操作是被删除的
	std::atomic 不支持移动构造和移动赋值
	<编译器被允许消除对std::atomic的冗余操作>
	使用std::atomic变量可能比互斥量提供更好的性能，但是它只适合操作单个变量或内存位置。

	volatile 是告诉编译器我们正在处理特殊内存。意味着告诉编译器"不要对这块内存执行任何优化"
	最常见的"特殊"内存是用来做内存映射I/O的内存。
	<在处理特殊内存时，必须保留看似冗余访问和无用存储的事实>
*/
#include <iostream>
#include <atomic>
using namespace std;

int main()
{
	std::atomic<int> ai(0);         //初始化ai为0
	ai = 10;                        //原子性地设置ai为10
	std::cout << ai << std::endl;   //原子性地读取ai的值, 注意: 但不保证整个语句的执行是原子的
	++ai;                           //原子性地递增ai到11
	--ai;                           //原子性地递减ai到10
	
	std::atomic<int> y(ai.load());           //读x
	y.store(ai.load());                      //再次读x
	//y = ai;											//编译错误, 拷贝/赋值操作是被删除的
	return 0;
}

// 编译:命令
// g++ item_40_atomic.cpp -o main