#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(0) {
        if (capacity > 0) {
            cache[0] = 0; // Fibonacci 0
            if (capacity > 1) {
                cache[1] = 1; // Fibonacci 1
                cached = 2; // 记录已计算的数量
            }
        }
    }

    // 复制构造器被删除
    DynFibonacci(DynFibonacci const &) = delete;

    // 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 如果缓存中已经计算出该 Fibonacci
        if (i < cached) {
            return cache[i];
        }
        
        // 计算 Fibonacci 并缓存结果
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1; // 更新已缓存的数量
        return cache[i];
    }

    // const 方法，返回已计算的 Fibonacci 值
    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib; // 应校验 C++ 中复制构造的操作
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
