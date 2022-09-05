#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "aop/aop.h"

namespace aop::test {

class MacrosTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

#define AOP_TEST_STR__(x) #x
#define AOP_TEST_STR_(x) AOP_TEST_STR__(x)
#define AOP_TEST_STR(x) AOP_TEST_STR_(x)

TEST_F(MacrosTest, AOP_GENERATE_ASPECT_NAME_TEST) {
    SNAPSHOT(AOP_TEST_STR(AOP_GENERATE_ASPECT_NAME));
}

}  // namespace aop::test
