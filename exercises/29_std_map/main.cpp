#include "../exercise.h"
#include <map>

// READ: `std::map` <https://zh.cppreference.com/w/cpp/container/map>
// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>
/*std::map：有序的关联容器。查找、插入和删除的时间复杂度为O(logn)适用于需要按键顺序进行操作的场景。
 std::unordered_map：无序的关联容器。平均情况下查找、插入和删除的时间复杂度为O( 1).适用于只需要快速查找、插入和删除，而不关心元素顺序的场景。*/
 template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    // TODO: 实现函数
     // 使用 find 方法查找键
     auto it = map.find(key);

     // 如果迭代器不等于 map.end()，表示找到了键
     return it != map.end();
 }

template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    // TODO: 实现函数
    map[key] = value;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    using namespace std::string_literals;

    std::map<std::string, std::string> secrets;

    set(secrets, "hello"s, "world"s);
    ASSERT(key_exists(secrets, "hello"s), "\"hello\" shoud be in `secrets`");
    ASSERT(!key_exists(secrets, "foo"s), "\"foo\" shoud not be in `secrets`");

    set(secrets, "foo"s, "bar"s);
    set(secrets, "Infini"s, "Tensor"s);
    ASSERT(secrets["hello"] == "world", "hello -> world");
    ASSERT(secrets["foo"] == "bar", "foo -> bar");
    ASSERT(secrets["Infini"] == "Tensor", "Infini -> Tensor");

    set(secrets, "hello"s, "developer"s);
    ASSERT(secrets["hello"] == "developer", "hello -> developer");

    return 0;
}
