#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "aop/aop.h"

namespace aop {

class AOPUtilityTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(AOPUtilityTest, GetProxyFunc) {
    {
        auto f1 = [](int x, int y, int &z) -> std::string {
            EXPECT_EQ(x, 1);
            EXPECT_EQ(y, 1);
            ++z;
            EXPECT_EQ(z, 2);

            return "f1";
        };

        auto f2 = [](int x, int y, int &z) -> int {
            EXPECT_EQ(x, 1);
            EXPECT_EQ(y, 1);
            ++z;
            EXPECT_EQ(z, 3);
            return 2;
        };

        auto f = [&f1, &f2](int x, int y, int &z) {
            auto p = AOPUtility::GetProxyFunc(x, y, z);
            auto f1_ = p(f1);
            auto f2_ = p(f2);

            EXPECT_EQ(f1_, "f1");
            EXPECT_EQ(f2_, 2);
        };

        int z = 1;
        f(1, 1, z);
    }
}

}  // namespace aop
