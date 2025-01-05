#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    static int num_a ;

    A() {
        ++num_a;
    }
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

int A::num_a = 0;
struct B final : public A {
    // TODO: 正确初始化静态字段
    static int num_b ;

    B() {
        ++num_b;
    }
  /*  这个问题的根本原因在于基类 A 没有定义虚析构函数。当你通过基类指针 A *ab 来删除一个派生类 B 的对象时，
    如果没有虚析构函数，那么只有基类部分会被销毁，而派生类 B 的析构函数不会被调用。这会导致 B::num_b 不会减少，因此它的值不会变为 0。*/
    ~B() override {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    //构造B一定会构造A
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    B &bb = *static_cast<B*>(ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
