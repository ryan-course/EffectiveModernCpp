
## std::unique_ptr

std::unique_ptr是原始指针的替代品, 内存中包含指向对象的指针,可能还会有一个自定义删除器
它没有控制块

## std::shared_ptr

std::shared_ptr对象在内存中是这样:

![item19_fig1](https://res.weread.qq.com/wrepub/CB_CXzB11B2U8t76Yb6YC_file2.png)
