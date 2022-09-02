#pragma once

#include "aop/aop.h"

#include "../aspect/a.h"
#include "../aspect/b.h"
#include "../aspect/c.h"
#include "../aspect/d.h"

namespace aop::test {

class A {
public:
    A() {}
    ~A() {}

    int Hello(int& x) {
        AOP_DECLARE_FUNC_BEGIN(AOPExecuteContext, hello, x)
        AOP_DECLARE_FUNC_ASPECT(aspect::A())
        AOP_DECLARE_FUNC_END()
    }

    int hello(int x) {
        return x;
    }

    void Hello2(int x) {
        AOP_DECLARE_FUNC_BEGIN(AOPExecuteContext, hello2, x)
        AOP_DECLARE_FUNC_END()
    }

    void hello2([[maybe_unused]] int x) {}

    int Hello3(int x) {
        AOP_DECLARE_FUNC_BEGIN(AOPExecuteContext, hello3, x)
        AOP_DECLARE_FUNC_ASPECT(aspect::B())
        AOP_DECLARE_FUNC_END()
    }

    int hello3(int& x) {
        return x;
    }

    int Hello4(int x) {
        AOP_DECLARE_FUNC_BEGIN(AOPExecuteContext, hello4, x)
        AOP_DECLARE_FUNC_ASPECT(aspect::C())
        AOP_DECLARE_FUNC_ASPECT(aspect::D())
        AOP_DECLARE_FUNC_END()
    }

    int hello4(int& x) {
        return x;
    }
};

}  // namespace aop::test
