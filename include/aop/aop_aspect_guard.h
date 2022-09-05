#ifndef AOP_AOP_ASPECT_GUARD_H
#define AOP_AOP_ASPECT_GUARD_H

#include <functional>

namespace aop {

template <typename T>
class AOPAspectGuard {
public:
    struct Options {
        std::function<void()> before{nullptr};
        std::function<void()> after{nullptr};
    };

    class Builder {
    public:
        Builder& WithBefore(std::function<void()> before) {
            options_.before = before;
            return *this;
        }

        Builder& WithAfter(std::function<void()> after) {
            options_.after = after;
            return *this;
        }

        AOPAspectGuard<T> Build(T* aspect) {
            auto a = AOPAspectGuard<T>(aspect, std::move(options_));
            a.Before();
            return a;
        }

    private:
        Options options_;
    };

public:
    AOPAspectGuard(T* aspect, Options&& options) : aspect_(aspect), options_(std::move(options)) {}

    ~AOPAspectGuard() {
        if (options_.after) {
            options_.after();
        }

        if (aspect_) {
            delete aspect_;
        }
    }

    void Before() {
        if (options_.before) {
            options_.before();
        }
    }

private:
    T* aspect_{nullptr};

    Options options_;
};

}  // namespace aop

#endif  // AOP_AOP_ASPECT_GUARD_H
