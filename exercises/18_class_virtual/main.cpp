#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG); // D 的虚函数为 C 的最终实现
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG); // rab 的实际类型是 B
    ASSERT(rbc.virtual_name() == 'C', MSG); // rbc 的实际类型是 C
    ASSERT(rcd.virtual_name() == 'C', MSG); // rcd 的实际类型是 D，调用 C 的虚函数
    ASSERT(rab.direct_name() == 'B', MSG); // rab 的实际类型是 B
    ASSERT(rbc.direct_name() == 'C', MSG); // rbc 的实际类型是 C
    ASSERT(rcd.direct_name() == 'D', MSG); // rcd 的实际类型是 D

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG); // rac 实际类型是 C
    ASSERT(rbd.virtual_name() == 'C', MSG); // rbd 实际类型是 D，调用 C 的虚函数
    ASSERT(rac.direct_name() == 'C', MSG); // rac 实际类型是 C
    ASSERT(rbd.direct_name() == 'D', MSG); // rbd 实际类型是 D

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); // rad 实际类型是 D，调用 C 的虚函数
    ASSERT(rad.direct_name() == 'D', MSG); // rad 实际类型是 D

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
