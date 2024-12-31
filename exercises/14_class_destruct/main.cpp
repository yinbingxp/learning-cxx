#include <iostream>
#include <cassert>

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(0) {
        // 初始化前两个斐波那契数
        if (capacity > 0) {
            cache[0] = 0; // fibonacci(0)
            cached++;
        }
        if (capacity > 1) {
            cache[1] = 1; // fibonacci(1)
            cached++;
        }
    }

    // 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache; // 释放动态分配的数组
    }

    // 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 检查索引是否在范围内
        if (i < 0 || i >= cached) {
            return 0; //或抛出异常
        }
        // 如果缓存中没有计算过的值，进行计算
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    assert(fib.get(10) == 55); // 确保 fibonacci(10) 应该是 55
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
