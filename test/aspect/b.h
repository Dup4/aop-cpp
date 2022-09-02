#pragma once

namespace aop::test::aspect {

class B {
public:
    class Aspect {
    public:
        template <typename C>
        void Before(C& ctx, [[maybe_unused]] int& res, int& x) {
            if (x == 2) {
                res = 5;
                ctx.is_break = true;
                return;
            }

            ++x;
        }

        template <typename C>
        void After([[maybe_unused]] C& ctx, [[maybe_unused]] int& res, [[maybe_unused]] int& x) {
            return;
        }
    };

public:
    Aspect* BuildPtr() {
        return new Aspect();
    }
};

}  // namespace aop::test::aspect
