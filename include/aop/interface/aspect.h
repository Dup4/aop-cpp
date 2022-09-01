#ifndef AOP_INTERFACE_ASPECT_H
#define AOP_INTERFACE_ASPECT_H

namespace aop {

template <typename T>
class Aspect {
protected:
    class AOPInternalInit {
    public:
    };
};

}  // namespace aop

#endif  // AOP_INTERFACE_ASPECT_H
