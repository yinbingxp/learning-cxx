#include <cassert>
#include <cstddef>
#include <utility>

class DynFibonacci {
    size_t *cache;
    int cached; // 实际计算的斐波那契数的数量
    int capacity; // 数组的容量

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]{}), cached(0), capacity(capacity) {
        // 初始化前两个斐波那契数
        if (capacity > 0) cache[0] = 0;
        if (capacity > 1) cache[1] = 1;
        cached = (capacity > 2) ? 2 : capacity; // 缓存当前计算数量
    }

    // 移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept 
        : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        other.cache = nullptr; // 防止析构时删除缓存
        other.cached = 0;
        other.capacity = 0;
    }

    // 移动赋值
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) { // 防止自赋值
            delete[] cache; // 释放当前对象的缓存
            cache = other.cache;
            cached = other.cached;
            capacity = other.capacity;
            other.cache = nullptr; // 防止析构时删除缓存
            other.cached = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 优化的斐波那契计算
    size_t operator[](int i) {
        if (i >= cached) {
            for (int j = cached; j <= i; ++j) {
                cache[j] = cache[j - 1] + cache[j - 2]; // 计算下一个斐波那契数
            }
            cached = i + 1; // 更新缓存数量
        }
        return cache[i];
    }

    // 不要修改这个方法
    size_t operator[](int i) const {
        assert(i < cached && "i out of range");
        return cache[i];
    }

    // 不要修改这个方法
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    assert(fib[10] == 55 && "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    assert(!fib.is_alive() && "Object moved");
    assert(fib_[10] == 55 && "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0); // 自赋值不应出错
    assert(fib0[10] == 55 && "fibonacci(10) should be 55");

    return 0;
}
