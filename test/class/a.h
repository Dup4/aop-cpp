#pragma once

#include "aop/aop.h"

namespace aop::test {

class A {
public:
    A() {}
    ~A() {}

    int Hello(int x) {
        AOP_DECLARE_FUNC_BEGIN(hello, x)
        AOP_DECLARE_FUNC_END()
    }

    int hello(int x) {
        return x;
    }

    // void Hello2(int x) {
    //     AOP_DECLARE_FUNC_BEGIN(hello2, x)
    //     AOP_DECLARE_FUNC_END()
    // }

    // void hello2([[maybe_unused]] int x) {}
};

}  // namespace aop::test
