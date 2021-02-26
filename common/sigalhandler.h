
#pragma once
#include <functional>

using SignalFuncPtr = std::function<void()>;

struct Signal {
    void signal(int sig, const SignalFuncPtr& handler);
};