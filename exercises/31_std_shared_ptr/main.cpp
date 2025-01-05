#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "");

//将 ptrs[0] 的所有权转移给 std::ignore 并丢弃它。这不会改变引用计数，因为 std::ignore 是一个临时变量。
    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "");//为什么是2？

    //observer.lock() 返回一个新的 shared_ptr，指向相同对象，引用计数增加到 3。
    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "");

    //shared = nullptr;释放 shared 的引用，引用计数减少到 2。 
    //for (auto &ptr : ptrs) ptr = nullptr;释放所有 ptrs 中的引用，引用计数减少到 0。
    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    //lock() 方法尝试获取一个 std::shared_ptr<int>，
    //如果 observer 观察的对象仍然存在，则返回一个指向该对象的 std::shared_ptr；
    //如果对象已经被销毁，则返回一个空的 std::shared_ptr。
    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");//为什么是0？

    return 0;
}
