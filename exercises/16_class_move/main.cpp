#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// 左值有明确地址，指有名称的对象，可以多次使用
// 右值没有固定地址，只能使用一次
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// 移动语义允许将资源从一个对象“搬”到另一个对象，而不是复制
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>
//移动构造函数接管了源对象的资源，并将其转移到新对象中。
// 移动赋值运算符的作用——它允许你将资源从一个对象转移到另一个已经存在的对象中。
// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(2) {
        if (capacity <= 2) {
            throw std::invalid_argument("Cache capacity too small");
        }
        cache[0] = 0;
        cache[1] = 1;
        for (int i = 2; i < capacity; ++i) {
            cache[i] = 0;// 初始化剩余部分为0
        }
    }

    // TODO: 实现移动构造器，右值引用，表示other是一个临时对象或即将被移动的对象
    //移动构造函数：用于创建新对象时直接接管另一个对象的资源。它不涉及自赋值问题，因为它是用来创建新对象的。
    DynFibonacci(DynFibonacci &&other) noexcept : cache(other.cache), cached(other.cached){
        other.cache = nullptr;//将源对象指针置为nullptr，避免析构时释放两次
    };

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
  /*  移动赋值运算符：用于更新一个已经存在的对象，使其接管另一个对象的资源。
    它需要处理自赋值问题，并清理现有资源，以确保不会发生内存泄漏。
 */
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this==&other) {
            return *this;//自赋值检查
        }

        //清理现有资源
        delete[] cache;

        //接管资源
        cache = other.cache;
        cached = other.cached;

        //将源对象指针设置为nullptr
        other.cache = nullptr;

        return *this;
    };

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache;
    };

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        for (; cached<=i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    //安全访问缓存数据
    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    //会调用移动构造器
    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    //调用移动赋值运算符
    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
