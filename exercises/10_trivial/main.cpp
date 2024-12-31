#include <iostream>
#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16] = {0}; // 初始化缓存
    int cached = 0; // 初始化缓存计数
};

// 实现缓存优化的斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    if (i < 0 || i >= 16) {
        throw std::out_of_range("Input index is out of range");
    }
    
    // 如果已经计算过，直接返回缓存的结果
    if (cache.cached > i) {
        return cache.cache[i];
    }

    // 计算并缓存斐波那契数
    for (int j = cache.cached; j <= i; ++j) {
        if (j == 0) {
            cache.cache[j] = 0;
        } else if (j == 1) {
            cache.cache[j] = 1;
        } else {
            cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];
        }
    }

    // 更新缓存计数
    cache.cached = i + 1;
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // 初始化缓存结构体，让计算能正确
    FibonacciCache fib;
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
