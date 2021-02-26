

#pragma once
#include <functional>

struct ExitCaller {
    ~ExitCaller() { functor_(); }
    ExitCaller(std::function<void()>&& functor)
        : functor_(std::move(functor)) {}
private:
    std::function<void()> functor_;
};

// This is a example.
// void funcX() {
//     int fd = open(fn, O_RDONLY);
//     if (fd < 0) {
//     }
//     ExitCaller ec1([=]{ close(fd); });
//     ....
// }