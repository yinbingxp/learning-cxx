#include "../exercise.h"

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    // 修改构造函数，使其支持模板推导
    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // 复制shape并计算总大小
        for (int i = 0; i < 4; i++) {
            shape[i] = shape_[i];  // 修正：之前错误地使用了shape_[4]
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    Tensor4D &operator+=(Tensor4D const &others) {
        // 计算当前tensor的总大小
        unsigned int size = shape[0] * shape[1] * shape[2] * shape[3];
        
        // 处理广播加法
        for (unsigned int i = 0; i < shape[0]; i++) {
            unsigned int i_other = others.shape[0] == 1 ? 0 : i;
            for (unsigned int j = 0; j < shape[1]; j++) {
                unsigned int j_other = others.shape[1] == 1 ? 0 : j;
                for (unsigned int k = 0; k < shape[2]; k++) {
                    unsigned int k_other = others.shape[2] == 1 ? 0 : k;
                    for (unsigned int l = 0; l < shape[3]; l++) {
                        unsigned int l_other = others.shape[3] == 1 ? 0 : l;
                        
                        // 计算当前位置的索引
                        unsigned int idx = ((i * shape[1] + j) * shape[2] + k) * shape[3] + l;
                        // 计算other tensor中对应位置的索引
                        unsigned int other_idx = ((i_other * others.shape[1] + j_other) * 
                                                 others.shape[2] + k_other) * others.shape[3] + l_other;
                        
                        data[idx] += others.data[other_idx];
                    }
                }
            }
        }
        return *this;
    }

    ~Tensor4D() {
        delete[] data;
    }

    // // 禁止复制和移动
    // Tensor4D(Tensor4D const &) = delete;
    // Tensor4D(Tensor4D &&) noexcept = delete;
};
// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D<int>(shape, data);
        auto t1 = Tensor4D<int>(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D<float>(s0, d0);
        auto t1 = Tensor4D<float>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D<double>(s0, d0);
        auto t1 = Tensor4D<double>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}