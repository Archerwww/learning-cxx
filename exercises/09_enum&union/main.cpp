#include "../exercise.h"

// READ: 枚举类型 <https://zh.cppreference.com/w/cpp/language/enum>

// `enum` 是 C 的兼容类型，本质上其对应类型的常量。
// 在 `enum` 中定义标识符等价于定义 constexpr 常量，即被看作是编译时的常量表达式
// 这些标识符不需要前缀，可以直接引用。
// 因此 `enum` 定义会污染命名空间，即将其成员设置为全局常量。
//无作用域枚举可以隐式地转换为整数类型
enum ColorEnum : unsigned char {
    COLOR_RED = 31,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
};

// 有作用域枚举型是 C++ 引入的类型安全枚举。
// 其内部标识符需要带前缀引用，如 `Color::Red`。
// 作用域枚举型可以避免命名空间污染，并提供类型安全保证。
//有作用域枚举不允许隐式转换为整数或其他枚举类型，需要显式的转换
enum class Color : int {
    Red = COLOR_RED,
    Green,
    Yellow,
    Blue,
};

ColorEnum convert_by_pun(Color c) {
    // READ: <https://zh.cppreference.com/w/cpp/language/union>
    // `union` 表示在同一内存位置存储的不同类型的值。
    // 其常见用法是实现类型双关转换，即将一种类型的值转换为另一种无关类型的值。
    // 但这种写法实际上仅在 C 语言良定义，在 C++ 中是未定义行为。
    // 这是比较少见的 C++ 不与 C 保持兼容的特性。
    // READ: 类型双关 <https://tttapa.github.io/Pages/Programming/Cpp/Practices/type-punning.html>
    //union TypePun {
    //    ColorEnum e;
    //    Color c;
    //};

    //TypePun pun;
    //// TODO: 补全类型双关转换

    //return pun.e;
    ColorEnum result;
    //std::memcpy通过复制内存内容来实现类型转换，确保不会违反别名规则
    //&result是目标地址，&c是源地址，sizeof(result)指定要复制的字节数，返回给定类型result的大小
    std::memcpy(&result, &c, sizeof(result));
    return result;
}

int main(int argc, char **argv) {
    ASSERT(convert_by_pun(Color::Red) == COLOR_RED, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Green) == COLOR_GREEN, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Yellow) == COLOR_YELLOW, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Blue) == COLOR_BLUE, "Type punning conversion");
    return 0;
}
