#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 3, ""); // 3个shared_ptr指向同一个int
    
    ptrs[0].reset();
    ASSERT(observer.use_count() == 2, ""); // 重置ptrs[0]，剩下2个shared_ptr指向int

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 1, ""); // 重置ptrs[1]，剩下1个shared_ptr指向int

    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, ""); // ptrs[2]是新的shared_ptr，不影响原有的weak_ptr

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, ""); // 重新将ptrs[0] 和 ptrs[1] 指向原来的shared_ptr，ptrs[2]转移所有权

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, ""); // ptrs[0] 被忽略，ptrs[1]仍指向有效的shared_ptr

    shared = observer.lock();
    ASSERT(observer.use_count() == 2, ""); // 通过lock获取到shared指针，use_count不变

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, ""); // 所有shared_ptr被重置，use_count变为0

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, ""); // 依然没有shared_ptr引用对象

    return 0;
}
