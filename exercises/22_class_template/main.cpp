﻿#include "../exercise.h"

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

   Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        for (auto i = 0u; i < 4; ++i) {
            shape[i] = shape_[i];
            /*通过乘法累加每个维度的大小，计算出总的元素数量。
            通过乘法累加每个维度的大小，计算出总的元素数量。*/
            size *= shape[i];
        }
        //为data动态分配内存
        data = new T[size];
        //复制数据
        std::memcpy(data, data_, size * sizeof(T));
    }
    ~Tensor4D() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 这个加法需要支持“单向广播”。
    // 具体来说，`others` 可以具有与 `this` 不同的形状，形状不同的维度长度必须为 1。
    // `others` 长度为 1 但 `this` 长度不为 1 的维度将发生广播计算。
    // 例如，`this` 形状为 `[1, 2, 3, 4]`，`others` 形状为 `[1, 2, 1, 4]`，
    // 则 `this` 与 `others` 相加时，3 个形状为 `[1, 2, 1, 4]` 的子张量各自与 `others` 对应项相加。
    Tensor4D &operator+=(Tensor4D const &others) {
        // TODO: 实现单向广播的加法
        // 预先存储每个阶是否需要广播
        bool broadcast[4];
        for (auto i = 0u; i < 4; ++i)
            if (broadcast[i] = shape[i] != others.shape[i])// 如果形状不一致就需要广播
                ASSERT(others.shape[i] == 1, "!");         // 单向广播，others 的对应长度必须为 1

        auto dst = this->data; // 要加到的元素地址
        auto src = others.data;// 要加上的元素地址
        T *marks[4]{src};      // 4 个阶的锚点
        for (auto i0 = 0u; i0 < shape[0]; ++i0) {

            if (broadcast[0]) src = marks[0];// 如果这个阶是广播的，回到锚点位置
            marks[1] = src;                  // 记录下一阶锚点。
            //锚点的主要作用是在广播过程中保存每个维度的起始位置，以便在需要重复数据时能够正确地重置指针。这样可以确保广播操作的正确性和效率。
            //通过使用锚点，我们能够在复杂的多维广播中保持指针的位置控制，从而实现正确的逐元素加法操作。

            for (auto i1 = 0u; i1 < shape[1]; ++i1) {

                if (broadcast[1]) src = marks[1];
                marks[2] = src;

                for (auto i2 = 0u; i2 < shape[2]; ++i2) {

                    if (broadcast[2]) src = marks[2];
                    marks[3] = src;

                    for (auto i3 = 0u; i3 < shape[3]; ++i3) {

                        if (broadcast[3]) src = marks[3];
                        *dst++ += *src++;
                    }
                }
            }
        }

        return *this;
    }
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
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
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

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
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

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}