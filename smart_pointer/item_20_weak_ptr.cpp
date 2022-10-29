/*
	当从std::shared_ptr上创建std::weak_ptr时两者指向相同的对象，但是std::weak_ptr不会影响所指对象的引用计数
	  两者的大小是相同的，使用相同的控制块（参见Item19），构造、析构、赋值操作涉及(第二个)引用计数的原子操作
	  在控制块中还是有第二个引用计数，std::weak_ptr操作的是第二个引用计数
	
	用std::weak_ptr替代可能会悬空的std::shared_ptr
	**weak_ptr常用于检测缓存是否过期, 和观察者列表**
	**weak_ptr能防止循环引用**, 
			(如果AB都使用shared_ptr指向对方,就会导致循环引用; 应该A使用shared_ptr指向B,B使用weak_ptr指向A)

	std::weak_ptr不能解引用，也不能测试是否为空值
	可以使用`expired`方法测试是否为悬空指针

*/

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Widget
{
public:
	// void process();
};

int main()
{
	auto spw =							  // spw创建之后，指向的Widget的
		 std::make_shared<Widget>(); //引用计数（ref count，RC）为1。
											  // std::make_shared的信息参见条款21

	std::weak_ptr<Widget> wpw(spw); // wpw指向与spw所指相同的Widget。RC仍为1

	spw = nullptr; // RC变为0，Widget被销毁。
	// wpw 现在悬空

	if (wpw.expired())
	{ //如果wpw没有指向对象…
		cout << "wpw is expired" << endl;
	}

	std::shared_ptr<Widget> spw1 = wpw.lock(); //如果wpw过期，spw1就为空
	if (!spw1)
	{
		cout << "spw1 is expired" << endl;
	}
	auto spw2 = wpw.lock(); //同上，但是使用auto
	if (!spw2)
	{
		cout << "spw2 is expired" << endl;
	}

	std::shared_ptr<Widget> spw3(wpw);          //如果wpw过期，抛出std::bad_weak_ptr异常


	return 0;
}

std::shared_ptr<const Widget> fastLoadWidget(WidgetID id)
{
    static std::unordered_map<WidgetID,			//hash表容器
                              std::weak_ptr<const Widget>> cache;
                                        //译者注：这里std::weak_ptr<const Widget>是高亮
    auto objPtr = cache[id].lock();     //objPtr是去缓存对象的
                                        //std::shared_ptr（或
                                        //当对象不在缓存中时为null）

    if (!objPtr) {                      //如果不在缓存中
        objPtr = loadWidget(id);        //加载它
        cache[id] = objPtr;             //缓存它
    }
    return objPtr;
}


// 编译:命令
// g++ item_20_weak_ptr.cpp -o main; ./main