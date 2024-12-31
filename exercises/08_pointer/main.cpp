﻿#include "../exercise.h"

// READ: 数组向指针退化 <https://zh.cppreference.com/w/cpp/language/array#%E6%95%B0%E7%BB%84%E5%88%B0%E6%8C%87%E9%92%88%E7%9A%84%E9%80%80%E5%8C%96>
bool is_fibonacci(int *ptr, int len, int stride) {
    ASSERT(len >= 3, "`len` should be at least 3");
    
    // 遍历指针，从索引 0 开始到 len - 3，检查是否满足斐波那契条件
    for (int i = 0; i < len - 2; ++i) {
        // 计算当前元素和下一个元素对应的值
        if (*(ptr + i) + *(ptr + i + 1) != *(ptr + i + 2)) {
            return false; // 如果不满足斐波那契条件，返回 false
        }
        i += stride - 1; // 根据 stride 增加 i
    }

    return true; // 如果所有条件都满足，返回 true
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    int arr0[]{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55},
        arr1[]{0, 1, 2, 3, 4, 5, 6},
        arr2[]{99, 98, 4, 1, 7, 2, 11, 3, 18, 5, 29, 8, 47, 13, 76, 21, 123, 34, 199, 55, 322, 0, 0};
    // clang-format off
    ASSERT( is_fibonacci(arr0    , sizeof(arr0) / sizeof(*arr0)    , 1),         "arr0 is Fibonacci"    );
    ASSERT( is_fibonacci(arr0 + 2, sizeof(arr0) / sizeof(*arr0) - 4, 1), "part of arr0 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr1    , sizeof(arr1) / sizeof(*arr1)    , 1),         "arr1 is not Fibonacci");
    ASSERT( is_fibonacci(arr1 + 1,  3                              , 1), "part of arr1 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2    , sizeof(arr2) / sizeof(*arr2)    , 1),         "arr2 is not Fibonacci");
    ASSERT( is_fibonacci(arr2 + 2, 10                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT( is_fibonacci(arr2 + 3,  9                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2 + 3, 10                              , 2), "guard check"                  );
    ASSERT(!is_fibonacci(arr2 + 1, 10                              , 2), "guard check"                  );
    // clang-format on
    return 0;
}
