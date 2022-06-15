#include <gtest/gtest.h>

#include "decorator/decorator.h"

class DecoratorTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

template <typename T>
class DecoratorForA {
public:
    int Show() {
        return derived().show() + 1;
    }

private:
    T& derived() {
        return static_cast<T&>(*this);
    }
};

class A : public DecoratorForA<A> {
    using Base = DecoratorForA<A>;
    friend class DecoratorForA<A>;

private:
    int show() {
        return 1;
    }
};

TEST_F(DecoratorTest, decorator_test) {
    A a;

    EXPECT_EQ(a.Show(), 2);
}
