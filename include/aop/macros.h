#ifndef AOP_MACROS_H
#define AOP_MACROS_H

#include <functional>
#include <memory>
#include <type_traits>

#include "./aop_execute_context.h"
#include "./aop_utility.h"

#define AOP_DECLARE_FUNC_BEGIN(ContextType, func, ...)                                                   \
    using ReturnType = std::decay_t<decltype(func(__VA_ARGS__))>;                                        \
    auto __aop_internal_res = ::aop::AOPUtility::GetInitValue<ReturnType>();                             \
    auto __aop_internal_ctx = ContextType{};                                                             \
                                                                                                         \
    [[maybe_unused]] auto proxy_args_func = std::invoke([&]() {                                          \
        if constexpr (std::is_void_v<ReturnType>) {                                                      \
            return ::aop::AOPUtility::GetProxyFunc(__aop_internal_ctx, __VA_ARGS__);                     \
        } else {                                                                                         \
            return ::aop::AOPUtility::GetProxyFunc(__aop_internal_ctx, __aop_internal_res, __VA_ARGS__); \
        }                                                                                                \
    });                                                                                                  \
                                                                                                         \
    std::function<void()> before_func = []() {};                                                         \
    std::function<void()> after_func = []() {};                                                          \
    auto execute_func = [&]() {                                                                          \
        __aop_internal_res = ::aop::AOPUtility::GetExecuteFuncValue<ReturnType>([&]() {                  \
            return func(__VA_ARGS__);                                                                    \
        });                                                                                              \
    };

#define AOP_DECLARE_FUNC_ASPECT(aspect)                                                          \
    {                                                                                            \
        using AspectType = std::remove_pointer_t<decltype(aspect.BuildPtr())>;                   \
        std::shared_ptr<AspectType> a = nullptr;                                                 \
        a.reset(aspect.BuildPtr());                                                              \
                                                                                                 \
        before_func = ::aop::AOPUtility::ConcatFuncByQueue(before_func,                          \
                                                           proxy_args_func([a](auto&&... args) { \
                                                               a->Before(args...);               \
                                                           }),                                   \
                                                           __aop_internal_ctx);                  \
                                                                                                 \
        after_func = ::aop::AOPUtility::ConcatFuncByStack(after_func,                            \
                                                          proxy_args_func([a](auto&&... args) {  \
                                                              a->After(args...);                 \
                                                          }),                                    \
                                                          __aop_internal_ctx);                   \
    }

#define AOP_DECLARE_FUNC_END()                      \
    before_func();                                  \
                                                    \
    if (!__aop_internal_ctx.is_break) {             \
        execute_func();                             \
    }                                               \
                                                    \
    after_func();                                   \
                                                    \
    return std::invoke([&]() {                      \
        if constexpr (std::is_void_v<ReturnType>) { \
            return;                                 \
        } else {                                    \
            return __aop_internal_res;              \
        }                                           \
    });

#endif  // AOP_MACROS_H
