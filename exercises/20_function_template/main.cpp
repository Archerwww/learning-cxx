#include "../exercise.h"

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
//template 关键字告诉编译器接下来是一个模板声明。


// 辅助函数：比较两个浮点数是否足够接近
template<typename T>
bool nearly_equal(T a, T b, T epsilon = T(1e-5)) {
    return std::abs(a - b) <= epsilon * std::max(1.0, std::max(std::abs(a), std::abs(b)));
}

template<class T>
T plus(T a, T b) {
    return a + b;
}


int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    //直接使用 == 比较浮点数 适用场景：当你可以确保两个浮点数是完全相同的，并且它们来源于同一个计算路径或初始化方式时，可以使用 ==
    //必须判断差值（相对误差 适用场景：大多数情况下，特别是当你对浮点数进行了数学运算（如加法、乘法等）后，应该使用相对误差来比较两个浮点数是否足够接近。
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过
    ASSERT(nearly_equal(plus<double>(0.1, 0.2), 0.3), "How to make this pass?");
    return 0;
}
