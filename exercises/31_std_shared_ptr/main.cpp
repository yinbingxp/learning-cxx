#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);        // 计数: 1
    std::shared_ptr<int> ptrs[]{shared, shared, shared}; // 计数: 4

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");          // 1个原始 + 3个数组中的拷贝

    ptrs[0].reset();                                // 计数: 3
    ASSERT(observer.use_count() == 3, "");          // reset释放一个引用

    ptrs[1] = nullptr;                              // 计数: 2
    ASSERT(observer.use_count() == 2, "");          // 赋值nullptr释放一个引用

    ptrs[2] = std::make_shared<int>(*shared);      // 计数: 1
    ASSERT(observer.use_count() == 1, "");          // ptrs[2]指向新对象，原对象只剩shared

    ptrs[0] = shared;                               // 计数: 2
    ptrs[1] = shared;                               // 计数: 3
    ptrs[2] = std::move(shared);                    // 计数: 2 (shared变为nullptr)
    ASSERT(observer.use_count() == 3, "");          // 移动后shared为空，只剩数组中的引用

    std::ignore = std::move(ptrs[0]);               // 计数不变
    ptrs[1] = std::move(ptrs[1]);                  // 计数不变
    ptrs[1] = std::move(ptrs[2]);                  // ptrs[2]变空，计数: 1
    ASSERT(observer.use_count() == 2, "");          // 只剩ptrs[1]持有引用

    shared = observer.lock();                       // 计数: 2
    ASSERT(observer.use_count() == 3, "");          // lock()创建新的shared_ptr

    shared = nullptr;                               // 计数: 1
    for (auto &ptr : ptrs) ptr = nullptr;          // 计数: 0
    ASSERT(observer.use_count() == 0, "");          // 所有shared_ptr都释放

    shared = observer.lock();                       // 对象已释放，返回nullptr
    ASSERT(observer.use_count() == 0, "");          // 没有有效引用

    return 0;
}