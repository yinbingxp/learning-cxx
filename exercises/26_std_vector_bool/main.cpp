#include "../exercise.h"
#include <vector>
#include <iostream>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true); // 构造函数，创建一个大小为 100 的 vector<bool>，所有元素初始化为 true
    ASSERT(vec[0], "Make this assertion pass."); // 第一个元素为 true
    ASSERT(vec[99], "Make this assertion pass."); // 第 100 个元素也为 true
    ASSERT(vec.size() == 100, "Make this assertion pass."); // 确认大小为 100
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl; // 输出 vector 的大小
    ASSERT(sizeof(vec) == sizeof(bool*), "Fill in the correct value."); // vector<bool> 的大小等于一个指针的大小
    
    {
        vec[20] = false; // 将第 21 个元素设置为 false
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`."); // 确认第 21 个元素为 false
    }
    
    {
        vec.push_back(false); // 向后推入一个 false
        ASSERT(vec.size() == 101, "Fill in the correct value."); // 确认大小为 101
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`."); // 第 101 个元素应为 false
    }
    
    {
        auto ref = vec[30]; // 引用第 31 个元素
        ASSERT(ref, "Fill in `ref` or `!ref`"); // 确认为 true
        ref = false; // 将引用的值设置为 false
        ASSERT(!ref, "Fill in `ref` or `!ref`"); // 确认引用的值为 false
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`."); // 确保 vec[30] 仍然为 false
    }
    return 0;
}
