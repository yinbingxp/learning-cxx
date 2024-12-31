﻿#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Fill in the correct value.");  // 数组大小
        ASSERT(sizeof(arr) == 5 * sizeof(int), "Fill in the correct value.");  // 数组所占字节数
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(arr.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");  // 数组内容比较
    }
    {
        std::array<double, 8> arr;
        ASSERT(arr.size() == 8, "Fill in the correct value.");  // 数组大小
        ASSERT(sizeof(arr) == 8 * sizeof(double), "Fill in the correct value.");  // 数组所占字节数
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Fill in the correct value.");  // 数组大小
        ASSERT(sizeof(arr) == 21 * sizeof(char), "Fill in the correct value.");  // 数组所占字节数
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value.");  // 字符串比较
    }
    return 0;
}
