/*
	
*/
#include <iostream>
#include <vector>
#include <array>
using namespace std;

int main()
{
	//vector只保存了指向堆内存中容器内容的指针
	std::vector<int> vm1;
	//把vw1移动到vw2。以常数时间运行。只有vw1和vw2中的指针被改变
	auto vm2 = std::move(vm1);

	//std::array没有这种指针实现，数据就保存在std::array对象中
	std::array<int, 10000> aw1;
	//把aw1移动到aw2。以线性时间运行。aw1中所有元素被移动到aw2
	auto aw2 = std::move(aw1);


	return 0;
}

// 编译:命令
// g++ item_29_move.cpp -o main; ./main