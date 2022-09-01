#ifndef AOP_MACROS_H
#define AOP_MACROS_H

#include <functional>
#include <type_traits>

#include "./aop_execute_context.h"
#include "./aop_utility.h"

#define AOP_DECLARE_FUNC_BEGIN(func, ...)                                    \
    using ReturnType = std::remove_reference_t<decltype(func(__VA_ARGS__))>; \
    auto res = AOPUtility::GetInitValue<ReturnType>();                       \
    auto ctx = AOPExecuteContext{};                                          \
                                                                             \
    [[maybe_unused]] auto proxy_args_func = std::invoke([&]() {              \
        if constexpr (std::is_void_v<ReturnType>) {                          \
            return AOPUtility::GetProxyFunc(ctx, __VA_ARGS__);               \
        } else {                                                             \
            return AOPUtility::GetProxyFunc(ctx, res, __VA_ARGS__);          \
        }                                                                    \
    });                                                                      \
                                                                             \
    auto before_func = []() {};                                              \
    auto after_func = []() {};                                               \
    auto execute_func = [&]() {                                              \
        res = AOPUtility::GetExecuteFuncValue<ReturnType>([&]() {            \
            return func(__VA_ARGS__);                                        \
        });                                                                  \
    };

#define AOP_DECLARE_FUNC_ASPECT(aspect)                                                    \
    {                                                                                      \
        auto a = aspect;                                                                   \
        before_func = AOPUtility::ConcatFuncByQueue(before_func,                           \
                                                    proxy_args_func([&a](auto&&... args) { \
                                                        a.Before(args);                    \
                                                    }),                                    \
                                                    ctx);                                  \
                                                                                           \
        after_func = AOPUtility::ConcatFuncByStack(after_func,                             \
                                                   proxy_args_func([&a](auto&&... args) {  \
                                                       a.After(args);                      \
                                                   }),                                     \
                                                   ctx);                                   \
    }

#define AOP_DECLARE_FUNC_END()                      \
    if (!ctx.is_break) {                            \
        before_func();                              \
    }                                               \
                                                    \
    if (!ctx.is_break) {                            \
        execute_func();                             \
    }                                               \
                                                    \
    if (!ctx.is_break) {                            \
        after_func();                               \
    }                                               \
                                                    \
    return std::invoke([&]() {                      \
        if constexpr (std::is_void_v<ReturnType>) { \
            return;                                 \
        } else {                                    \
            return res;                             \
        }                                           \
    });

#endif  // AOP_MACROS_H
