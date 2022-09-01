#ifndef AOP_AOP_UTILITY_H
#define AOP_AOP_UTILITY_H

#include <utility>

namespace aop {

class AOPUtility {
public:
    template <typename... Args>
    static auto GetProxyFunc(Args&&... args) {
        return [&](auto&& Func) {
            return Func(std::forward<Args>(args)...);
        };
    }
};

}  // namespace aop

#endif  // AOP_AOP_UTILITY_H
