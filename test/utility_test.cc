#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "aop/utility.h"

namespace aop::test {

class UtilityTest : public testing::Test {
public:
    void Hello() {}

protected:
    virtual void SetUp() override {}
};

TEST_F(UtilityTest, GetFuncName) {
    {
        auto s = Utility::GetFuncName("UtilityTest::Hello");
        std::string expected_s = "Hello";
        EXPECT_EQ(s, expected_s);
    }
}

}  // namespace aop::test
