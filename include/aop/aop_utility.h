#ifndef AOP_AOP_UTILITY_H
#define AOP_AOP_UTILITY_H

#include <utility>

#include "./aop_execute_context.h"

namespace aop {

class AOPUtility {
public:
    template <typename... Args>
    static auto GetProxyFunc(Args&&... args) {
        return [&](auto&& Func) {
            return Func(std::forward<Args>(args)...);
        };
    }

    template <typename PreFunc, typename Func, typename Context>
    static auto ConcatFuncByQueue(PreFunc&& pre_func, Func&& func, Context& ctx) {
        return [&]() {
            pre_func();

            if (ctx.is_break) {
                return;
            }

            func();
        };
    }

    template <typename PreFunc, typename Func, typename Context>
    static auto ConcatFuncByStack(PreFunc&& pre_func, Func&& func, Context& ctx) {
        return [&]() {
            func();

            if (ctx.is_break) {
                return;
            }

            pre_func();
        };
    }
};

}  // namespace aop

#endif  // AOP_AOP_UTILITY_H
