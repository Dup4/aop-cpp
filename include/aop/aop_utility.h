#ifndef AOP_AOP_UTILITY_H
#define AOP_AOP_UTILITY_H

#include <type_traits>
#include <utility>

#include "./aop_execute_context.h"

namespace aop {

class AOPUtility {
public:
    template <typename T, std::enable_if_t<std::is_void_v<T>, bool> = true>
    static auto GetInitValue() {
        return 0;
    }

    template <typename T, std::enable_if_t<!std::is_void_v<T>, bool> = true>
    static auto GetInitValue() {
        return T{};
    }

    template <typename T, std::enable_if_t<std::is_void_v<T>, bool> = true, typename Func>
    static auto GetExecuteFuncValue(Func&& func) {
        func();
        return 0;
    }

    template <typename T, std::enable_if_t<!std::is_void_v<T>, bool> = true, typename Func>
    static auto GetExecuteFuncValue(Func&& func) {
        return func();
    }

    template <typename... Args>
    static auto GetProxyFunc(Args&&... args) {
        return [&](auto&& func) {
            return [&, func = func]() {
                return func(std::forward<Args>(args)...);
            };
        };
    }

    template <typename PreFunc, typename Func, typename Context>
    static auto ConcatFuncByQueue(PreFunc&& pre_func, Func&& func, [[maybe_unused]] Context& ctx) {
        return [pre_func, func]() {
            pre_func();
            func();
        };
    }

    template <typename PreFunc, typename Func, typename Context>
    static auto ConcatFuncByStack(PreFunc&& pre_func, Func&& func, [[maybe_unused]] Context& ctx) {
        return [pre_func, func]() {
            func();
            pre_func();
        };
    }
};

}  // namespace aop

#endif  // AOP_AOP_UTILITY_H
