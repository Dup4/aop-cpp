#ifndef AOP_MACROS_H
#define AOP_MACROS_H

#include <functional>
#include <memory>
#include <type_traits>

#include "./aop_execute_context.h"
#include "./aop_utility.h"

#define AOP_DECLARE_FUNC_BEGIN(ContextType, func, ...)              \
    using ReturnType = std::decay_t<decltype(func(__VA_ARGS__))>;   \
    auto res = AOPUtility::GetInitValue<ReturnType>();              \
    auto ctx = ContextType{};                                       \
                                                                    \
    [[maybe_unused]] auto proxy_args_func = std::invoke([&]() {     \
        if constexpr (std::is_void_v<ReturnType>) {                 \
            return AOPUtility::GetProxyFunc(ctx, __VA_ARGS__);      \
        } else {                                                    \
            return AOPUtility::GetProxyFunc(ctx, res, __VA_ARGS__); \
        }                                                           \
    });                                                             \
                                                                    \
    std::function<void()> before_func = []() {};                    \
    std::function<void()> after_func = []() {};                     \
    auto execute_func = [&]() {                                     \
        res = AOPUtility::GetExecuteFuncValue<ReturnType>([&]() {   \
            return func(__VA_ARGS__);                               \
        });                                                         \
    };

#define AOP_DECLARE_FUNC_ASPECT(aspect)                                                   \
    {                                                                                     \
        auto* a = aspect.BuildPtr();                                                      \
        before_func = AOPUtility::ConcatFuncByQueue(before_func,                          \
                                                    proxy_args_func([a](auto&&... args) { \
                                                        a->Before(args...);               \
                                                    }),                                   \
                                                    ctx);                                 \
                                                                                          \
        after_func = AOPUtility::ConcatFuncByStack(after_func,                            \
                                                   proxy_args_func([a](auto&&... args) {  \
                                                       a->After(args...);                 \
                                                       delete a;                          \
                                                   }),                                    \
                                                   ctx);                                  \
    }

#define AOP_DECLARE_FUNC_END()                      \
    before_func();                                  \
                                                    \
    if (!ctx.is_break) {                            \
        execute_func();                             \
    }                                               \
                                                    \
    after_func();                                   \
                                                    \
    return std::invoke([&]() {                      \
        if constexpr (std::is_void_v<ReturnType>) { \
            return;                                 \
        } else {                                    \
            return res;                             \
        }                                           \
    });

#endif  // AOP_MACROS_H
