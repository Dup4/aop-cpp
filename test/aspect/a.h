#pragma once

namespace aop::test::aspect {

class A {
public:
    class Aspect {
    public:
        template <typename C>
        void Before([[maybe_unused]] C& ctx, [[maybe_unused]] int& res, int& x) {
            ++x;
        }

        template <typename C>
        void After([[maybe_unused]] C& ctx, int& res, [[maybe_unused]] int& x) {
            ++res;
        }
    };

public:
    Aspect* BuildPtr() {
        return new Aspect();
    }
};

}  // namespace aop::test::aspect
