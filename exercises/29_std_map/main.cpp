#include "../exercise.h"
#include <map>

// 检查键是否存在于map中
template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    return map.find(key) != map.end(); // 如果找到key，返回true；否则返回false
}

// 设置map中指定键的值
template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    map[key] = value; // 使用赋值运算符来插入或更新值
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
