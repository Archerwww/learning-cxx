#include "../exercise.h"

// 使用迭代而非递归计算斐波那契数
constexpr unsigned long long fibonacci(int i) {
    if (i <= 1) {
        return i;
    }

    unsigned long long a = 0, b = 1;
    for (int n = 2; n <= i; ++n) {
        unsigned long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // 对于较大的数值，移除 constexpr 关键字以避免编译时计算问题
    const auto ANS_N = 90;
    auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}




//#include "../exercise.h"
//
//constexpr unsigned long long fibonacci(int i) {
//    //使用迭代而非递归
//    if (i<=1) {
//        return i;
//    }
//
//    unsigned long long a = 0, b = 1, c;
//    for (int n = 2; n < =i; ++n) {
//        c = a + b;
//        a = b;
//        b = c;
//    }
//    return b;
//
//    /*switch (i) {
//        case 0:
//            return 0;
//        case 1:
//            return 1;
//        default:
//            return fibonacci(i - 1) + fibonacci(i - 2);
//    }*/
//}
//
//int main(int argc, char **argv) {
//    constexpr auto FIB20 = fibonacci(20);
//    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
//    std::cout << "fibonacci(20) = " << FIB20 << std::endl;
//
//    // TODO: 观察错误信息，修改一处，使代码编译运行
//    // PS: 编译运行，但是不一定能算出结果……
//    //最简单的方法是移除 constexpr 关键字，
//     //这样 fibonacci 函数将在运行时执行，而不是在编译时。虽然这解决了编译问题，但它可能会导致运行时性能下降，特别是对于大数值。
//    constexpr auto ANS_N = 90;
//    constexpr auto ANS = fibonacci(ANS_N);
//    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;
//    return 0;
//}


//#include "../exercise.h"
//
//unsigned long long fibonacci(int i, int level = 0) {
//    for (int j = 0; j < level; ++j) {
//        std::cout << ": ";
//    }
//    std::cout << i << std::endl;
//    switch (i) {
//        case 0:
//            return 0;
//        case 1:
//            return 1;
//        default:
//            return fibonacci(i - 1, level + 1) + fibonacci(i - 2, level + 1);
//    }
//}
//
//int main(int argc, char **argv) {
//    constexpr auto ANS_N = 5;
//    auto ANS = fibonacci(ANS_N);
//    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;
//    return 0;
//}