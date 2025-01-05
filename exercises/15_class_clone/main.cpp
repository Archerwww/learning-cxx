#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        if (capacity <= 2) {
            throw std::invalid_argument("Cache capacity too small");
        }
        cache[0] = 0;
        cache[1] = 1;
        for (int i = 2; i < capacity; ++i) {
            cache[i] = 0;// 初始化剩余部分为0
        }
    }

    // TODO: 实现复制构造器
    DynFibonacci(DynFibonacci const &others)
        : cache(new size_t[others.cached]),
          cached(others.cached) {
        //std:memcpy可以在复制构造函数中高效的复制缓存数组的内容，适用于简平铺的数据结构
        //如果对象中包含复杂的数据类型或指针，建议逐个元素进行深拷贝，以确保正确处理所有资源
        std::memcpy(cache, others.cache, cached * sizeof(size_t));
    }

    // 显式弃置复制构造器
    //DynFibonacci(const DynFibonacci &) = delete;


    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    };

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
