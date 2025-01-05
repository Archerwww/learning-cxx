#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 5 * sizeof(int), "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        //std::memcmp：这是一个C标准库函数，用来逐字节地比较两个内存块的内容。它接受三个参数：
        //第一个参数是指向第一个内存块起始位置的指针。
        //第二个参数是指向第二个内存块起始位置的指针。
        //第三个参数是要比较的字节数。
        //如果两个内存块完全相同，则 std::memcmp 返回0；否则，它返回一个非零值，表示差异。
        ASSERT(std::memcmp(arr.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::array<double, 8> arr;
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 8 * sizeof(double), "Fill in the correct value.");
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");
        //arr.data() 是 C++ 标准库中 std::array 容器类的一个成员函数。它返回一个指向数组首元素的指针，即返回的是容器内部存储的数据的直接地址。
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value.");
    }
    return 0;
}
