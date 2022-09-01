#ifndef AOP_AOP_CONTEXT_H
#define AOP_AOP_CONTEXT_H

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace aop {

class AOPContext {
public:
    struct ClassNode {
        std::string class_name{""};
        std::vector<std::string> func_name_list{};
    };

public:
    AOPContext() {}
    virtual ~AOPContext() {}

    static AOPContext& Instance() {
        static AOPContext aop_context;
        return aop_context;
    }

    void RegisterClass(std::string_view class_name) {
        auto c = ClassNode{};
        c.class_name = class_name;
        mp[class_name] = c;
    }

    void RegisterFunc(std::string_view class_name, std::string_view func_name) {
        mp[class_name].func_name_list.push_back(std::string(func_name));
    }

    std::unordered_map<std::string_view, ClassNode> mp;
};

}  // namespace aop

#endif  // AOP_AOP_CONTEXT_H
