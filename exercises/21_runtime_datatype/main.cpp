#include "../exercise.h"
#include <cmath>

enum class DataType {
    Float,
    Double,
};

/// @brief Tagged union 即标签化联合体，是联合体的一种常见应用。
///        Rust enum 在实现上就是标签化联合体。
struct TaggedUnion {
    DataType type;
    // NOTICE: struct/union 可以相互任意嵌套。
    union {
        float f;
        double d;
    };
};

// TODO: 将这个函数模板化用于 sigmoid_dyn
//这个函数计算并返回给定数值的 Sigmoid 函数值。
// Sigmoid 函数是一个常见的数学函数，广泛应用于机器学习中，特别是作为神经网络中的激活函数。
//它将任何输入值转换为一个介于 0 和 1 之间的值。
template <typename T>
T sigmoid(T x) {
    return 1 / (1 + std::exp(-x));
}

//虽然 sigmoid 是模板函数，但直接传递 TaggedUnion 给它会导致编译错误，
//因为 TaggedUnion 不是一个数值类型，而是一个包含不同类型数据的结构体。
//模板函数不能自动解析出 TaggedUnion 内部的具体数值类型,
//所以要使用sigmoid_dyn
    TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};
    // TODO: 根据 type 调用 sigmoid
    if (x.type==DataType::Float) {
        ans.f = sigmoid(x.f);
    } else if (x.type==DataType::Double) {
        ans.d = sigmoid(x.d);
    }
    return ans;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    TaggedUnion xf{DataType::Float};
    xf.f = 5.f;
    auto yf = sigmoid_dyn(xf);
    ASSERT(yf.type == DataType::Float, "type mismatch");
    ASSERT(yf.f == 1 / (1 + std::exp(-5.f)), "sigmoid float");

    TaggedUnion xd{DataType::Double};
    xd.d = 5.0;
    auto yd = sigmoid_dyn(xd);
    ASSERT(yd.type == DataType::Double, "type mismatch");
    ASSERT(yd.d == 1 / (1 + std::exp(-5.0)), "sigmoid double");
    return 0;
}
