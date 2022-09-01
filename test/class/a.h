#pragma once

#include "aop/aop.h"

namespace aop::test {

class A : public aop::Register<A> {
public:
    A() {}
    ~A() {}

    AOP_DECLARE_FUNC_BEGIN(Hello, void)
    AOP_DECLARE_FUNC_END()

    template <typename T>
    AOP_DECLARE_FUNC_BEGIN(Hello2, void, [[maybe_unused]] T t)
    AOP_DECLARE_FUNC_END()
};

}  // namespace aop::test
