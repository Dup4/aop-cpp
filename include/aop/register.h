#ifndef AOP_REGISTER_CLASS_H
#define AOP_REGISTER_CLASS_H

#include <string>
#include <string_view>

#include "./aop_context.h"
#include "./utility.h"

namespace aop {

template <typename T>
class Register {
protected:
    class AOPInternalInit {
    public:
        AOPInternalInit() : aop_context_(AOPContext::Instance()), class_name_(Utility::GetPrettyClassTypeName<T>()) {
            aop_context_.RegisterClass(class_name_);
        }

        void RegisterFunc(std::string_view func_name) {
            aop_context_.RegisterFunc(class_name_, func_name);
        }

    private:
        std::string class_name_{""};
        AOPContext& aop_context_;
    };

    inline static AOPInternalInit aop_internal_init_{};
};

}  // namespace aop

#endif  // AOP_REGISTER_CLASS_H
