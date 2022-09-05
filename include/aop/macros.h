#ifndef AOP_MACROS_H
#define AOP_MACROS_H

#include <functional>
#include <memory>
#include <string>
#include <type_traits>

#include "./aop_aspect_guard.h"
#include "./aop_execute_context.h"
#include "./aop_utility.h"

#define AOP_CONCAT_ASPECT_NAME_(prefix, line, counter) prefix##_##line##_##counter
#define AOP_CONCAT_ASPECT_NAME(prefix, line, counter) AOP_CONCAT_ASPECT_NAME_(prefix, line, counter)
#define AOP_GENERATE_ASPECT_NAME AOP_CONCAT_ASPECT_NAME(AOP_ASPECT_NAME, __LINE__, __COUNTER__)

#define AOP_DECLARE_FUNC_BEGIN(ContextType, func, ...)                                                         \
    using ReturnType = std::decay_t<decltype(func(__VA_ARGS__))>;                                              \
    auto __aop_internal_res = ::aop::AOPUtility::GetInitValue<ReturnType>();                                   \
    auto __aop_internal_ctx = ContextType{};                                                                   \
                                                                                                               \
    {                                                                                                          \
        [[maybe_unused]] auto proxy_args_func = std::invoke([&]() {                                            \
            if constexpr (std::is_void_v<ReturnType>) {                                                        \
                return ::aop::AOPUtility::GetProxyFunc(__aop_internal_ctx, ##__VA_ARGS__);                     \
            } else {                                                                                           \
                return ::aop::AOPUtility::GetProxyFunc(__aop_internal_ctx, __aop_internal_res, ##__VA_ARGS__); \
            }                                                                                                  \
        });                                                                                                    \
                                                                                                               \
        auto execute_func = [&]() {                                                                            \
            __aop_internal_res = ::aop::AOPUtility::GetExecuteFuncValue<ReturnType>([&]() {                    \
                return func(__VA_ARGS__);                                                                      \
            });                                                                                                \
        };                                                                                                     \
                                                                                                               \
        [[maybe_unused]] void* __aop_internal_aspect_ptr = nullptr;

#define AOP_DECLARE_FUNC_ASPECT(aspect)                                                                \
    __aop_internal_aspect_ptr = static_cast<void*>(aspect.BuildPtr());                                 \
                                                                                                       \
    [[maybe_unused]] auto AOP_GENERATE_ASPECT_NAME =                                                   \
            ::aop::AOPAspectGuard<std::remove_pointer_t<decltype(aspect.BuildPtr())>>::Builder()       \
                    .WithBefore(proxy_args_func([__aop_internal_aspect_ptr](auto&&... args) {          \
                        auto* a = static_cast<decltype(aspect.BuildPtr())>(__aop_internal_aspect_ptr); \
                        a->Before(args...);                                                            \
                    }))                                                                                \
                    .WithAfter(proxy_args_func([__aop_internal_aspect_ptr](auto&&... args) {           \
                        auto* a = static_cast<decltype(aspect.BuildPtr())>(__aop_internal_aspect_ptr); \
                        a->After(args...);                                                             \
                    }))                                                                                \
                    .Build(static_cast<decltype(aspect.BuildPtr())>(__aop_internal_aspect_ptr));       \
                                                                                                       \
    __aop_internal_aspect_ptr = nullptr;

#define AOP_DECLARE_FUNC_END()                      \
    if (!__aop_internal_ctx.is_break) {             \
        execute_func();                             \
    }                                               \
    }                                               \
                                                    \
    return std::invoke([&]() {                      \
        if constexpr (std::is_void_v<ReturnType>) { \
            return;                                 \
        } else {                                    \
            return __aop_internal_res;              \
        }                                           \
    });

#endif  // AOP_MACROS_H
