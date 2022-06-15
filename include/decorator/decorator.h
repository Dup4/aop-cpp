#ifndef DECORATOR_DECORATOR_H
#define DECORATOR_DECORATOR_H

template <typename T>
class DecoratorBaseCRTP {
public:
    DecoratorBaseCRTP() {}
    virtual ~DecoratorBaseCRTP() {}

protected:
    T& derived() {
        return static_cast<T&>(*this);
    }
};

#endif  // DECORATOR_DECORATOR_H
