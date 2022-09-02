#pragma once

namespace aop::test::aspect {

class C {
public:
    class Aspect {
    public:
        template <typename C>
        void Before([[maybe_unused]] C& ctx, [[maybe_unused]] int& res, int& x) {
            if (x == 1) {
                ++x;
            }
        }

        template <typename C>
        void After([[maybe_unused]] C& ctx, int& res, [[maybe_unused]] int& x) {
            if (res == 4) {
                ++res;
            }
        }
    };

public:
    Aspect* BuildPtr() {
        return new Aspect();
    }
};

}  // namespace aop::test::aspect
