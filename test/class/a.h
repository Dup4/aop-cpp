#pragma once

#include "aop/aop.h"

namespace aop::test {

class A : public aop::Register<A> {
public:
    A() {}
    ~A() {}

    AOP_DECLARE_FUNC_BEGIN(Hello, void)
    AOP_DECLARE_FUNC_END()
};

}  // namespace aop::test
