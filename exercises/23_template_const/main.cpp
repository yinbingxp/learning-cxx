#include "../exercise.h"
#include <cstring>

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;

    Tensor(unsigned int const shape_[N]) {
        // 保存形状并计算大小
        std::memcpy(shape, shape_, N * sizeof(unsigned int));
        unsigned int size = 1;
        for (unsigned int i = 0; i < N; ++i) {
            size *= shape[i];  // 计算总大小
        }
        data = new T[size];
        std::memset(data, 0, size * sizeof(T));  // 将数据初始化为0
    }
    
    ~Tensor() {
        delete[] data;  // 释放内存
    }

    // 为了保持简单，禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];  // 返回对应的元素
    }
    
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];  // 返回对应的元素（只读）
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        for (unsigned int i = 0; i < N; ++i) {
            ASSERT(indices[i] < shape[i], "Invalid index"); // 检查索引的有效性
            unsigned int stride = 1;
            for (unsigned int j = i + 1; j < N; ++j) {
                stride *= shape[j];  // 计算当前维度的步幅
            }
            index += indices[i] * stride;  // 转换为一维索引
        }
        return index; // 返回计算出来的一维索引
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1, "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
        ASSERT(tensor.data[119] == 2, "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
