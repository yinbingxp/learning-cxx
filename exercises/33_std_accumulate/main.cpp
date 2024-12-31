#include "../exercise.h"
#include <numeric>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};

    // 计算张量的元素总数
    int total_elements = std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<int>());
    
    // 每个 float 占用的字节数
    const int bytes_per_element = sizeof(DataType);
    
    // 计算总字节数
    int size = total_elements * bytes_per_element;

    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
