#pragma once

#include <map>
#include <string>

namespace aop::test::aspect {

class E {
public:
    class Node {
    public:
        void SetX(const std::string& v) {
            mp_["x"] = v;
        }

        std::string GetX() const {
            return mp_.at("x");
        }

    private:
        std::map<std::string, std::string> mp_{};
    };

public:
    class Aspect {
    public:
        template <typename C>
        void Before([[maybe_unused]] C& ctx, [[maybe_unused]] std::string& res) {
            node_.SetX("5");
        }

        template <typename C>
        void After([[maybe_unused]] C& ctx, std::string& res) {
            res = node_.GetX();
        }

    private:
        Node node_{};
    };

public:
    Aspect* BuildPtr() {
        return new Aspect();
    }
};

}  // namespace aop::test::aspect
