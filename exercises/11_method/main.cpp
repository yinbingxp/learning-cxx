#include <iostream>
#include <cassert>

struct Fibonacci {
    unsigned long long cache[128] = {0}; // 初始化缓存为0
    int cached = 2; // 已缓存的数量，初始缓存前两个 Fibonacci 数

    Fibonacci() {
        cache[0] = 0; // Fibonacci(0) = 0
        cache[1] = 1; // Fibonacci(1) = 1
    }

    // 计算指定索引的 Fibonacci 数
    unsigned long long get(int i) {
        // 检查并计算未缓存的 Fibonacci 数
        for (int j = cached; j <= i; ++j) {
            // 计算并存储 Fibonacci 数
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        // 更新缓存的数量
        cached = std::max(cached, i + 1);
        return cache[i];
    }
};

int main(int argc, char **argv) {
    Fibonacci fib;
    assert(fib.get(10) == 55); // 验证 Fibonacci(10) 应为 55
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
