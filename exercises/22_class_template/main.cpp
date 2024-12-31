#include <cstring>  // 为了使用 std::memcpy
#include "../exercise.h"
template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        std::memcpy(shape, shape_, 4 * sizeof(unsigned int)); // 复制形状
        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            size *= shape[i]; // 计算总大小
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T)); // 复制数据
    }

    ~Tensor4D() {
        delete[] data; // 释放内存
    }

    // 禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 这个加法需要支持“单向广播”。
    Tensor4D &operator+=(Tensor4D const &others) {
        // 检查形状是否可以广播
        for (int i = 0; i < 4; ++i) {
            if (shape[i] != others.shape[i] && shape[i] != 1 && others.shape[i] != 1) {
                throw std::invalid_argument("Incompatible shapes for broadcasting");
            }
        }

        // 执行加法
        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            size *= shape[i]; // 计算数据的总大小
        }

        // 进行广播加法
        for (unsigned int i = 0; i < size; ++i) {
            // 确定当前的维度索引
            unsigned int idx[4];
            unsigned int temp = i;
            for (int j = 3; j >= 0; --j) {
                idx[j] = temp % shape[j];
                temp /= shape[j];
            }

            // 计算对应的 `others` 的索引
            unsigned int others_idx[4];
            for (int j = 0; j < 4; ++j) {
                others_idx[j] = others.shape[j] == 1 ? 0 : idx[j];
            }

            data[i] += others.data[others_idx[0] + others.shape[0] * (others_idx[1] + others.shape[1] * (others_idx[2] + others.shape[2] * others_idx[3]))];
        }

        return *this;
    }
};
