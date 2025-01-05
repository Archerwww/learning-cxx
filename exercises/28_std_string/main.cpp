#include "../exercise.h"
#include <string>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>
//字符串字面量是你直接写在代码中的固定文本，比如 "Hello, world!"。 默认情况下，它们是 const char[] 类型。
//使用 std::string_literals 和 s 后缀可以让你直接创建 std::string 类型的对象，更加方便 
int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    using namespace std::string_literals;
    auto hello = "Hello"s;
    auto world = "world";
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    ASSERT((std::is_same_v<decltype(world), const char*>), "Fill in the missing type.");
    // TODO: 将 `?` 替换为正确的字符串
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    return 0;
}
