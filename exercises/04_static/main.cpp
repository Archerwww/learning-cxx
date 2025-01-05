#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？

//static修饰的函数只能在定义它的源文件中使用
static int func(int param) {
    static int static_ = param;
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++;
}

//static修饰的局部变量在首次进入其作用域时初始化，并在其整个程序运行期间保持其值
int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) ==5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}
