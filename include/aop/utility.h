#ifndef AOP_UTILITY_H
#define AOP_UTILITY_H

#include <memory>
#include <string>
#include <type_traits>

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

namespace aop {

class Utility {
public:
    template <typename T>
    static std::string GetClassTypeName(std::string_view custom_name = "") {
        return getClassTypeName<T>(custom_name, false);
    }

    template <typename T>
    static std::string GetPrettyClassTypeName(std::string_view custom_name = "") {
        return getClassTypeName<T>(custom_name, true);
    }

private:
    template <typename T>
    static std::string getClassTypeName(std::string_view custom_name, bool is_pretty) {
        if constexpr (std::is_pointer_v<T>) {
            return getClassTypeName<std::remove_pointer_t<T>>(custom_name, is_pretty);
        }

        std::string res = "";
        res += typeid(T).name();

        if (is_pretty) {
            res = demangle(res.data());
        }

        if (!custom_name.empty()) {
            res += ".";
            res += custom_name;
        }

        return res;
    }

    static std::string demangle(const char* mangled_name) {
#ifndef _MSC_VER
        std::size_t len = 0;
        int status = 0;
        std::unique_ptr<char, decltype(&std::free)> ptr(
                __cxxabiv1::__cxa_demangle(mangled_name, nullptr, &len, &status), &std::free);
        if (status == 0) {
            return std::string(ptr.get());
        }

        // fallback
        return mangled_name;
#else
        auto pos = strstr(mangled_name, " ");
        if (pos == nullptr) {
            return std::string{mangled_name};
        } else {
            return std::string{pos + 1};
        }
#endif
    }
};

}  // namespace aop

#endif  // AOP_UTILITY_H
