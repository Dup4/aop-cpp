#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "aop/aop.h"

#include "./class/a.h"

namespace aop::test {

class AOPTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(AOPTest, aop_test) {
    A a;
    int x = 1;
    EXPECT_EQ(a.Hello(x), 3);
}

}  // namespace aop::test
