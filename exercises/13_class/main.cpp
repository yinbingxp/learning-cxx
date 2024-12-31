#include <iostream>
#include <cassert>

class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 实现构造器
    Fibonacci() : cached(0) {
        // 初始值
        cache[0] = 0; // F(0) = 0
        cache[1] = 1; // F(1) = 1
    }

    // 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        if (i < 0 || i >= 16) {
            throw std::out_of_range("Index out of range");
        }
        
        // 如果缓存中已经有该值，直接返回
        if (i <= cached) {
            return cache[i];
        }

        // 计算并缓存
        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        
        cached = i; // 更新缓存索引
        return cache[i];
    }
};

int main(int argc, char **argv) {
    Fibonacci fib;
    assert(fib.get(10) == 55); // 断言 fibonacci(10) 应该等于 55
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
